#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button
{
protected:
	sf::RectangleShape m_button;

public:
	virtual ~Button() = default;
	Button() = default;
	
	Button(const sf::Vector2f& size, const sf::Color& bgColor);
	
	virtual void setBackColor(const sf::Color& color);
	virtual void setPosition(const sf::Vector2f& pos);

	virtual void drawTo(sf::RenderWindow& window) const;
	virtual bool isMouseOver(const sf::RenderWindow& window) const;

	Button(const Button&) = delete;
	Button(Button&&) = delete;

	Button& operator=(const Button&) = delete;
	Button& operator=(Button&&) = delete;
};

#endif