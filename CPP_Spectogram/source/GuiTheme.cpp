#include "GuiTheme.hpp"

GuiTheme::GuiTheme(GuiThemes theme)
{
	m_currentTheme = theme;
	updateTheme();
}

void GuiTheme::updateTheme()
{
	m_text = std::get<0>(m_defaultThemes.at(m_currentTheme));
	m_background = std::get<1>(m_defaultThemes.at(m_currentTheme));
	m_primaryButton = std::get<2>(m_defaultThemes.at(m_currentTheme));
	m_secondaryButton = std::get<3>(m_defaultThemes.at(m_currentTheme));
	m_accent = std::get<4>(m_defaultThemes.at(m_currentTheme));
}

void GuiTheme::SwapTheme()
{
	unsigned themeId = (static_cast<unsigned>(m_currentTheme) + 1) % 2;
	m_currentTheme = static_cast<GuiThemes>(themeId);

	updateTheme();
}

const sf::Color GuiTheme::getTextColor() const
{
	return m_text;
}

const sf::Color GuiTheme::getBackgroundColor() const
{
	return m_background;
}

const sf::Color GuiTheme::getPButtonColor() const
{
	return m_primaryButton;
}

const sf::Color GuiTheme::getSButtonColor() const
{
	return m_secondaryButton;
}

const sf::Color GuiTheme::getAccentColor() const
{
	return m_accent;
}