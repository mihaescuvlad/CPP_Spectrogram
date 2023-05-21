#include "GuiTheme.hpp"

GuiTheme::GuiTheme(Themes theme)
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

void GuiTheme::swapTheme()
{
	unsigned themeId = (static_cast<unsigned>(m_currentTheme) + 1) % 2;
	m_currentTheme = static_cast<Themes>(themeId);

	updateTheme();
}

sf::Color GuiTheme::getTextColor() const
{
	return m_text;
}

sf::Color GuiTheme::getBackgroundColor() const
{
	return m_background;
}

sf::Color GuiTheme::getPButtonColor() const
{
	return m_primaryButton;
}

sf::Color GuiTheme::getSButtonColor() const
{
	return m_secondaryButton;
}

sf::Color GuiTheme::getAccentColor() const
{
	return m_accent;
}

GuiTheme::Themes GuiTheme::getCurrentTheme() const
{
	return m_currentTheme;
}