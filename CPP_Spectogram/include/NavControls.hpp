#ifndef FILESYSTEM_NAV_CONTROLS_HPP
#define FILESYSTEM_NAV_CONTROLS_HPP

#include "SpriteButton.hpp"

class NavControls
{
private:
	SpriteButton m_nextPage;
	SpriteButton m_previousPage;
	SpriteButton m_closeTab;

public:
	NavControls(const SpriteButtonConfig& nextPage, const SpriteButtonConfig& previousPage, const SpriteButtonConfig& closeTab);

	void setNextPageButtonPosition(const sf::Vector2f& pos);
	void setPrevPageButtonPosition(const sf::Vector2f& pos);
	void setCloseTabButtonPosition(const sf::Vector2f& pos);
	void setControlsPosition(const sf::Vector2f& posNextPage, const sf::Vector2f& posPrevPage, const sf::Vector2f& posCloseTab);

	void drawTo(sf::RenderWindow& window) const;
};

#endif