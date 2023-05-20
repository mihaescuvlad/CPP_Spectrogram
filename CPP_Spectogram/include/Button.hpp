#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RectangleShape m_button;
	sf::Text m_text;

public:
	Button() = default;

	Button(const std::string& text, const sf::Vector2f& size, const unsigned& charSize, const sf::Color& bgColor, const sf::Color& textColor);

	void setFont(const sf::Font& font);
	void setBackColor(const sf::Color& color);
	void setTextColor(const sf::Color& color);
	void setPosition(const sf::Vector2f& pos);

	void drawTo(sf::RenderWindow& window) const;
	bool isMouseOver(const sf::RenderWindow& window) const;
};

#endif