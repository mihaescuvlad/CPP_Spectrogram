#ifndef GUI_THEME_HPP
#define GUI_THEME_HPP

#include <tuple>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Constants.hpp"

class GuiTheme
{
public:
	enum class GuiThemes : unsigned
	{
		LIGHT,
		DARK,
		INVALID_THEME
	};

private:
	typedef std::tuple<sf::Color, sf::Color, sf::Color, sf::Color, sf::Color> themeComponents;
	typedef std::unordered_map<GuiThemes, themeComponents> themeData;

	themeData m_defaultThemes{
		{GuiThemes::LIGHT, {
			Constants::LIGHT_TEXT,
			Constants::LIGHT_BACKGROUND,
			Constants::LIGHT_PRIMARY_BUTTON,
			Constants::LIGHT_SECONDARY_BUTTON,
			Constants::LIGHT_ACCENT
		}},
		{GuiThemes::DARK, {
			Constants::DARK_TEXT,
			Constants::DARK_BACKGROUND,
			Constants::DARK_PRIMARY_BUTTON,
			Constants::DARK_SECONDARY_BUTTON,
			Constants::DARK_ACCENT
		}},
		{GuiThemes::INVALID_THEME, {{},{},{},{},{}}}
	};

	GuiThemes m_currentTheme;

	sf::Color m_text;
	sf::Color m_background;
	sf::Color m_primaryButton;
	sf::Color m_secondaryButton;
	sf::Color m_accent;

public:
	GuiTheme(GuiThemes theme = GuiThemes::LIGHT);

	void updateTheme();
	void SwapTheme();

	const sf::Color getTextColor() const;
	const sf::Color getBackgroundColor() const;
	const sf::Color getPButtonColor() const;
	const sf::Color getSButtonColor() const;
	const sf::Color getAccentColor() const;
};

#endif