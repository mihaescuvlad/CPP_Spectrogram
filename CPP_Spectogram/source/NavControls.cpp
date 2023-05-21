#include "NavControls.hpp"

NavControls::NavControls(const SpriteButtonConfig& nextPage, const SpriteButtonConfig& previousPage, const SpriteButtonConfig& closeTab)
	: m_nextPage{ nextPage.m_size, nextPage.m_bg_color, nextPage.m_texture, nextPage.m_sprite_color },
	  m_previousPage{ previousPage.m_size, previousPage.m_bg_color, previousPage.m_texture, previousPage.m_sprite_color },
	  m_closeTab{ closeTab.m_size, closeTab.m_bg_color, closeTab.m_texture, closeTab.m_sprite_color }
{}


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