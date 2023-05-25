#include "NavControls.hpp"

NavControls::NavControls(const SpriteButtonConfig& nextPage, const SpriteButtonConfig& previousPage, const SpriteButtonConfig& closeTab)
	: m_nextPage{ nextPage.m_size, nextPage.m_bg_color, {}, nextPage.m_sprite_color },
	  m_previousPage{ previousPage.m_size, previousPage.m_bg_color, {}, previousPage.m_sprite_color },
	  m_closeTab{ closeTab.m_size, closeTab.m_bg_color, {}, closeTab.m_sprite_color }
{}

void NavControls::setNextPageColor(const sf::Color& color)
{
	m_nextPage.setBackColor(color);
}

void NavControls::setPrevPageColor(const sf::Color& color)
{
	m_previousPage.setBackColor(color);
}

void NavControls::setCloseTabColor(const sf::Color& color)
{
	m_closeTab.setBackColor(color);
}

void NavControls::updateTextures(const GuiTheme::Themes& theme)
{
	const std::vector<std::string> iconPaths = m_themeIcons.at(theme);
	m_nextPageIcon.loadFromFile(iconPaths.at(0));
	m_prevPageIcon.loadFromFile(iconPaths.at(1));
	m_closeTabIcon.loadFromFile(iconPaths.at(2));

	m_nextPage.setSpriteTexture(m_nextPageIcon);
	m_previousPage.setSpriteTexture(m_prevPageIcon);
	m_closeTab.setSpriteTexture(m_closeTabIcon);
}

bool NavControls::isMouseOverNextPage(const sf::RenderWindow& window) const
{
	return m_nextPage.isMouseOver(window);
}

bool NavControls::isMouseOverPrevPage(const sf::RenderWindow& window) const
{
	return m_previousPage.isMouseOver(window);
}

bool NavControls::isMouseOverCloseTab(const sf::RenderWindow& window) const
{
	return m_closeTab.isMouseOver(window);
}

void NavControls::setNextPageButtonPosition(const sf::Vector2f& pos)
{
	m_nextPage.setPosition(pos);
}

void NavControls::setPrevPageButtonPosition(const sf::Vector2f& pos)
{
	m_previousPage.setPosition(pos);
}

void NavControls::setCloseTabButtonPosition(const sf::Vector2f& pos)
{
	m_closeTab.setPosition(pos);
}

void NavControls::setControlsPosition(const sf::Vector2f& posNextPage, const sf::Vector2f& posPrevPage, const sf::Vector2f& posCloseTab)
{
	m_nextPage.setPosition(posNextPage);
	m_previousPage.setPosition(posPrevPage);
	m_closeTab.setPosition(posCloseTab);
}

void NavControls::drawTo(sf::RenderWindow& window) const
{
	m_nextPage.drawTo(window);
	m_previousPage.drawTo(window);
	m_closeTab.drawTo(window);
}