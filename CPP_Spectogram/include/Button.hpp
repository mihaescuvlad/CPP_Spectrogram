#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include <SFML/Graphics.hpp>

#include "GuiTheme.hpp"

class Button
{
protected:
	sf::RectangleShape m_button;

public:
	virtual ~Button() = default;
	Button() = default;
	
	Button(const sf::Vector2f& size, const sf::Color& bgColor, const sf::Vector2f& pos = {});
	
	virtual void setBackColor(const sf::Color& color);
	virtual void setPosition(const sf::Vector2f& pos);

	virtual sf::Vector2f getPosition() const;
	virtual float getHeight() const;

	virtual void drawTo(sf::RenderWindow& window) const;
	virtual bool isMouseOver(const sf::RenderWindow& window) const;

	Button(const Button&) = default;
	Button(Button&&) = default;

	Button& operator=(const Button&) = default;
	Button& operator=(Button&&) = default;
};

#endif