#ifndef FILESYSTEM_NAV_HPP
#define FILESYSTEM_NAV_HPP

#include <SFML\Graphics.hpp>

#include "IFileManager.hpp"
#include "NavControls.hpp"
#include "NavDetails.hpp"
#include "SpriteButton.hpp"
#include "TextButton.hpp"
#include "CurrentFileText.hpp"
#include "SpectrogramScreen.hpp"

class FilesystemNav
{
private:
	GuiTheme m_tabTheme;

	sf::RectangleShape m_tab;
	std::unique_ptr<IFileManager> m_fileManager;
	CurrentFileText& m_currentFileText;
	SpectrogramScreen& m_spectrogram;
	bool& m_displayNav;

	const sf::Vector2f m_firstOptionPosition;
	std::vector<TextButton> m_options;

	NavDetails m_details;
	NavControls m_controls;
	TextButtonConfig m_optionConfig;

	void setNavColor(const sf::Color& color);
	void setTextColor(const sf::Color& pathTextColor, const sf::Color& pageTextColor);
	void setControlColor(const sf::Color& nextPageColor, const sf::Color& prevPageColor, const sf::Color& closeTabColor);
	void updateOptionsColorScheme();

	static std::string getLastPart(const std::string& inputString);
	static std::string textWraparound(const std::string& inputString);
	static std::string textAddEllipsis(const std::string& inputString);
	static std::string processOptionString(const std::string& inputString);


	using range = std::ranges::subrange<std::vector<TextButton>::iterator, std::vector<TextButton>::iterator>;
	using const_range = std::ranges::subrange<std::vector<TextButton>::const_iterator, std::vector<TextButton>::const_iterator>;
	const_range getCurrentPageWorkingRange() const;
	range getCurrentPageWorkingRange();

	template<typename Self>
	static auto getCurrentPageWorkingRangeImpl(Self & self)
	{
		const auto [startPos, endPos] = self.m_details.getCurrentPageRange();
		const auto fileCount = self.m_options.size();
		const auto maxPos = std::min(endPos, fileCount);
		const auto length = maxPos - startPos;

		auto startIterator = std::next(self.m_options.begin(), static_cast<int64_t>(startPos));
		auto endIterator = std::next(startIterator, static_cast<int64_t>(length));

		return makePageWorkingRange(startIterator, endIterator);
	}

	using const_range_it = std::vector<TextButton>::const_iterator;
	using range_it = std::vector<TextButton>::iterator;

	static const_range makePageWorkingRange(const_range_it begin, const_range_it end);
	static range makePageWorkingRange(range_it begin, range_it end);

	bool isFirstOptionOnPage(size_t optionIterator) const;
	void updateOptionPositions();
	void updateOptions();
	void changePath(const std::filesystem::path& newPathTermination);
public:
	void updateColors();
	void setTheme(const GuiTheme& newTheme);

	void setDetailsPosition(const sf::Vector2f& posPath, const sf::Vector2f& posPage);
	void setControlsPosition(const sf::Vector2f& posNextPage, const sf::Vector2f& posPrevPage, const sf::Vector2f& posCloseTab);

	bool isMouseOverNextPage(const sf::RenderWindow& window);
	bool isMouseOverPrevPage(const sf::RenderWindow& window);
	bool isMouseOverCloseTab(const sf::RenderWindow& window);
	bool isMouseOverOption(const sf::RenderWindow& window);

	void pressNextPage();
	void pressPrevPage();
	void pressCloseTab();
	void pressOption(const sf::RenderWindow& window);


	void displayElementsOnPage(sf::RenderWindow& window) const;
	void drawTo(sf::RenderWindow& window) const;

	template<typename F>
		requires std::is_invocable_r_v<std::unique_ptr<IFileManager>, F>
	FilesystemNav(F&& fileManagerBuilder, const GuiTheme& theme, const sf::Vector2f& size, const sf::Vector2f& pos,
		const SpriteButtonConfig& nextPageButton, const SpriteButtonConfig& prevPageButton, const SpriteButtonConfig& closeTabButton,
		const NavDetailsConfig& navDetails, const TextButtonConfig& optionConfig, const sf::Vector2f& firstOptionPosition, CurrentFileText& currentFileText, SpectrogramScreen& spectrogram, bool& displayNav)
		:	m_firstOptionPosition{ firstOptionPosition },
			m_details{ navDetails.m_current_path, navDetails.m_page_count },
			m_controls{ nextPageButton, prevPageButton, closeTabButton }, m_optionConfig{ optionConfig },
		m_currentFileText{ currentFileText }, m_spectrogram{spectrogram}, m_displayNav{ displayNav }
	{
		m_fileManager = std::invoke(std::forward<F>(fileManagerBuilder));
		m_fileManager->updateDirectory(m_fileManager->getCurrentDirectory());
		m_details.setCurrentPath(m_fileManager);

		m_tabTheme = theme;

		updateOptions();
		updateOptionPositions();

		m_tab.setSize(size);
		m_tab.setPosition(pos);

		updateColors();
	}
};

#endif
