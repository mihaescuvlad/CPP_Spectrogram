#include "ThemeManager.hpp"

ThemeManager::ThemeManager(const sf::Vector2f& position, const sf::Vector2f& size) : m_changeThemeButton(size, m_guiTheme.getPButtonColor(), m_themeIcon)
{
	m_position = position;
	m_size = size;

	m_themeIcon.loadFromFile(m_themeIcons.at(m_guiTheme.getCurrentTheme()));
	m_changeThemeButton.setSpriteTexture(m_themeIcon);

	m_changeThemeButton.setPosition(m_position);
}

bool ThemeManager::isMouseOver(const sf::RenderWindow& window) const
{
	return m_changeThemeButton.isMouseOver(window);
}

void ThemeManager::swapTheme()
{
	m_guiTheme.swapTheme();

	m_themeIcon.loadFromFile(m_themeIcons.at(m_guiTheme.getCurrentTheme()));
	m_changeThemeButton.setSpriteTexture(m_themeIcon);
}

sf::Color ThemeManager::getTextColor() const
{
	return m_guiTheme.getTextColor();
}

sf::Color ThemeManager::getBackgroundColor() const
{
	return m_guiTheme.getBackgroundColor();
}

sf::Color ThemeManager::getPButtonColor() const
{
	return m_guiTheme.getPButtonColor();
}

sf::Color ThemeManager::getSButtonColor() const
{
	return m_guiTheme.getSButtonColor();
}

sf::Color ThemeManager::getAccentColor() const
{
	return m_guiTheme.getAccentColor();
}

GuiTheme::Themes ThemeManager::getCurrentTheme() const
{
	return m_guiTheme.getCurrentTheme();
}

void ThemeManager::update(const sf::RenderWindow& window)
{
	if (m_changeThemeButton.isMouseOver(window))
	{
		m_changeThemeButton.setBackColor(m_guiTheme.getAccentColor());
	}
	else
	{
		m_changeThemeButton.setBackColor(m_guiTheme.getPButtonColor());
	}
}

void ThemeManager::drawTo(sf::RenderWindow& window) const
{
	m_changeThemeButton.drawTo(window);
}