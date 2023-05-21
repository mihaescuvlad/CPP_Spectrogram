#include "FilesystemNav.hpp"

void FilesystemNav::displayElementsOnPage(sf::RenderWindow& window) const
{
	/// TODO: Implement File Select Buttons
	window.draw(m_tab);
}

void FilesystemNav::drawTo(sf::RenderWindow& window) const
{
	window.draw(m_tab);

	displayElementsOnPage(window);

	m_details.drawTo(window);
	m_controls.drawTo(window);
}