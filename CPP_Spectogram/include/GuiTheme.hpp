#ifndef GUI_THEME_HPP
#define GUI_THEME_HPP

#include <tuple>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Constants.hpp"

class GuiTheme
{
public:
	enum class Themes : unsigned
	{
		LIGHT,
		DARK,
		INVALID_THEME
	};

private:
	typedef std::tuple<sf::Color, sf::Color, sf::Color, sf::Color, sf::Color> themeComponents;
	typedef std::unordered_map<Themes, themeComponents> themeData;

	themeData m_defaultThemes{
		{Themes::LIGHT, {
			Constants::LIGHT_TEXT,
			Constants::LIGHT_BACKGROUND,
			Constants::LIGHT_PRIMARY_BUTTON,
			Constants::LIGHT_SECONDARY_BUTTON,
			Constants::LIGHT_ACCENT
		}},
		{Themes::DARK, {
			Constants::DARK_TEXT,
			Constants::DARK_BACKGROUND,
			Constants::DARK_PRIMARY_BUTTON,
			Constants::DARK_SECONDARY_BUTTON,
			Constants::DARK_ACCENT
		}},
		{Themes::INVALID_THEME, {{},{},{},{},{}}}
	};

	Themes m_currentTheme;

	sf::Color m_text;
	sf::Color m_background;
	sf::Color m_primaryButton;
	sf::Color m_secondaryButton;
	sf::Color m_accent;

public:
	GuiTheme(Themes theme = Themes::LIGHT);

	void updateTheme();
	void swapTheme();

	sf::Color getTextColor() const;
	sf::Color getBackgroundColor() const;
	sf::Color getPButtonColor() const;
	sf::Color getSButtonColor() const;
	sf::Color getAccentColor() const;
	Themes getCurrentTheme() const;
};

#endif