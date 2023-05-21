#ifndef FILESYSTEM_NAV_HPP
#define FILESYSTEM_NAV_HPP

#include <SFML\Graphics.hpp>

#include "BasicFileManager.hpp"
#include "IFileManager.hpp"
#include "NavControls.hpp"
#include "NavDetails.hpp"
#include "SpriteButton.hpp"
#include "TextButton.hpp"

class FilesystemNav
{
private:
	sf::RectangleShape m_tab;
	std::unique_ptr<IFileManager> m_fileManager;
	std::vector<TextButton> m_options;

	NavDetails m_details;
	NavControls m_controls;
public:
	template<typename F>
		requires std::is_invocable_r_v<std::unique_ptr<IFileManager>, F>
	FilesystemNav(F&& fileManagerBuilder, const sf::Vector2f& size, const sf::Color& bgColor, const sf::Vector2f& pos,
		const SpriteButtonConfig& nextPageButton, const SpriteButtonConfig& prevPageButton, const SpriteButtonConfig& closeTabButton,
		const NavDetailsConfig& navDetails)
		: m_details{ navDetails.m_current_path, navDetails.m_page_count }, m_controls{ nextPageButton, prevPageButton, closeTabButton }
	{
		m_fileManager = std::invoke(std::forward<F>(fileManagerBuilder));

		m_tab.setSize(size);
		m_tab.setFillColor(bgColor);
		m_tab.setPosition(pos);
	}

	void displayElementsOnPage(sf::RenderWindow& window) const;
	void drawTo(sf::RenderWindow& window) const;
};

#endif
