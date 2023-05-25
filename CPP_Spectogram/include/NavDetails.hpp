#ifndef FILESYSTEM_NAV_DETAILS_HPP
#define FILESYSTEM_NAV_DETAILS_HPP

#include <string>
#include <ranges>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "IFileManager.hpp"

struct TextNavDetailsConfig;

class NavDetails
{
private:
	sf::Text m_currentPath;
	sf::Text m_pageText;

	unsigned m_currentPage{};
	unsigned m_pageCount{};

	static unsigned computePageCount(unsigned fileCount);
public:
	NavDetails(const TextNavDetailsConfig& currentPath, const TextNavDetailsConfig& pageCount);

	void updatePageText();
	void setCurrentPath(const std::unique_ptr<IFileManager>& path);
	void setCurrentPage(unsigned page);
	void setPageCount(unsigned pageCount);
	void incrementPage();
	void decrementPage();

	void setPathColor(const sf::Color& color);
	void setPageColor(const sf::Color& color);

	void setPathPosition(const sf::Vector2f& pos);
	void setPagePosition(const sf::Vector2f& pos);

	unsigned getCurrentPage() const;
	unsigned getPageCount() const;
	std::pair<size_t, size_t> getCurrentPageRange() const;

	void drawTo(sf::RenderWindow& window) const;
};

struct TextNavDetailsConfig {
	const std::string& m_text;
	const unsigned m_char_size;
	const sf::Font& m_font;
	const sf::Color& m_text_color;
};

struct NavDetailsConfig {
	const TextNavDetailsConfig& m_current_path;
	const TextNavDetailsConfig& m_page_count;
};

#endif