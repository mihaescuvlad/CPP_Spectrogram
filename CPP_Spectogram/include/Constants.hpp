#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <filesystem>
#include <string>
#include <SFML/Graphics/Color.hpp>

class Constants
{
public:
	static const std::filesystem::path DEFAULT_FILE_PATH;

	static const sf::Color LIGHT_TEXT;
	static const sf::Color LIGHT_BACKGROUND;
	static const sf::Color LIGHT_PRIMARY_BUTTON;
	static const sf::Color LIGHT_SECONDARY_BUTTON;
	static const sf::Color LIGHT_ACCENT;

	static const sf::Color DARK_TEXT;
	static const sf::Color DARK_BACKGROUND;
	static const sf::Color DARK_PRIMARY_BUTTON;
	static const sf::Color DARK_SECONDARY_BUTTON;
	static const sf::Color DARK_ACCENT;

	static const std::string DEFAULT_FONT;
	static const sf::Color DEFAULT_ICON_COLOR;

	static const std::string LIGHT_THEME_ICON;
	static const std::string DARK_THEME_ICON;
	static const std::vector<std::string> LIGHT_NAV_ICONS;
	static const std::vector<std::string> DARK_NAV_ICONS;

	static const unsigned MAX_NAV_ELEMENT_COUNT;
	static const uint32_t MAX_CHARACTERS_PER_ROW;
	static const uint32_t MAX_CHARACTERS_TIL_ELLIPSING;
	static const uint32_t MAX_PATH_LENGTH;
};

#endif
