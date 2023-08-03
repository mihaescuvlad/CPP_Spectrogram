#include "Button.hpp"

Button::Button(const sf::Vector2f& size, const sf::Color& bgColor, const sf::Vector2f& pos)
{
	m_button.setSize(size);
	m_button.setFillColor(bgColor);

  Button::setPosition(pos);
}

void Button::setBackColor(const sf::Color& color)
{
	m_button.setFillColor(color);
}

void Button::setPosition(const sf::Vector2f& pos)
{
	m_button.setPosition(pos);
}

sf::Vector2f Button::getPosition() const
{
	return m_button.getPosition();
}

float Button::getHeight() const
{
	return m_button.getGlobalBounds().height;
}

void Button::drawTo(sf::RenderWindow& window) const
{
	window.draw(m_button);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const
{
	const float mouseX = static_cast<float>(sf::Mouse::getPosition(window).x);
	const float mouseY = static_cast<float>(sf::Mouse::getPosition(window).y);

	const float btnPosX = m_button.getPosition().x;
	const float btnPosY = m_button.getPosition().y;

	const float btnXPosWidth = m_button.getPosition().x + m_button.getLocalBounds().width;
	const float btnYPosHeight = m_button.getPosition().y + m_button.getLocalBounds().height;

	if (mouseX >= btnXPosWidth || mouseX <= btnPosX || mouseY >= btnYPosHeight || mouseY <= btnPosY)
	{
		return false;
	}

	return true;
}