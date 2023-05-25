#ifndef FILESYSTEM_NAV_CONTROLS_HPP
#define FILESYSTEM_NAV_CONTROLS_HPP

#include "SpriteButton.hpp"

class NavControls
{
private:
	typedef std::vector<std::string> ThemeData;

	std::unordered_map<GuiTheme::Themes, ThemeData> m_themeIcons{
		{GuiTheme::Themes::LIGHT, Constants::LIGHT_NAV_ICONS},
		{GuiTheme::Themes::DARK, Constants::DARK_NAV_ICONS },
		{GuiTheme::Themes::INVALID_THEME, {} }
	};
	sf::Texture m_nextPageIcon;
	sf::Texture m_prevPageIcon;
	sf::Texture m_closeTabIcon;

	SpriteButton m_nextPage;
	SpriteButton m_previousPage;
	SpriteButton m_closeTab;

public:
	NavControls(const SpriteButtonConfig& nextPage, const SpriteButtonConfig& previousPage, const SpriteButtonConfig& closeTab);

	void setNextPageColor(const sf::Color& color);
	void setPrevPageColor(const sf::Color& color);
	void setCloseTabColor(const sf::Color& color);
	void updateTextures(const GuiTheme::Themes& theme);

	bool isMouseOverNextPage(const sf::RenderWindow& window) const;
	bool isMouseOverPrevPage(const sf::RenderWindow& window) const;
	bool isMouseOverCloseTab(const sf::RenderWindow& window) const;

	void setNextPageButtonPosition(const sf::Vector2f& pos);
	void setPrevPageButtonPosition(const sf::Vector2f& pos);
	void setCloseTabButtonPosition(const sf::Vector2f& pos);
	void setControlsPosition(const sf::Vector2f& posNextPage, const sf::Vector2f& posPrevPage, const sf::Vector2f& posCloseTab);

	void drawTo(sf::RenderWindow& window) const;
};

#endif