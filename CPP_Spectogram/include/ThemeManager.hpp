#ifndef THEME_MANAGER_HPP
#define THEME_MANAGER_HPP
#include "GuiTheme.hpp"
#include "SpriteButton.hpp"

class ThemeManager {
private:
	std::unordered_map<GuiTheme::Themes, std::string> m_themeIcons{
		{GuiTheme::Themes::LIGHT, Constants::LIGHT_THEME_ICON },
		{GuiTheme::Themes::DARK, Constants::DARK_THEME_ICON },
		{GuiTheme::Themes::INVALID_THEME, {} }
	};

	sf::Vector2f m_position;
	sf::Vector2f m_size;
	GuiTheme m_guiTheme;
	sf::Texture m_themeIcon;
	SpriteButton m_changeThemeButton;

public:
	ThemeManager(const sf::Vector2f& position, const sf::Vector2f& size = { 50, 50 });

	bool isMouseOver(const sf::RenderWindow& window) const;
	void swapTheme();
	void update(const sf::RenderWindow& window);

	sf::Color getTextColor() const;
	sf::Color getBackgroundColor() const;
	sf::Color getPButtonColor() const;
	sf::Color getSButtonColor() const;
	sf::Color getAccentColor() const;
	GuiTheme::Themes getCurrentTheme() const;

	void drawTo(sf::RenderWindow& window) const;
};

#endif