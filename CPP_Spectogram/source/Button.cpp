#include "Button.hpp"

Button::Button(const std::string& text, const sf::Vector2f& size, const unsigned& charSize, const sf::Color& bgColor, const sf::Color& textColor)
{
	m_text.setString(text);
	m_text.setFillColor(textColor);
	m_text.setCharacterSize(charSize);

	m_button.setSize(size);
	m_button.setFillColor(bgColor);
}

void Button::setFont(const sf::Font& font)
{
	m_text.setFont(font);
}

void Button::setBackColor(const sf::Color& color)
{
	m_button.setFillColor(color);
}

void Button::setTextColor(const sf::Color& color)
{
	m_text.setFillColor(color);
}

void Button::setPosition(const sf::Vector2f& pos)
{
	m_button.setPosition(pos);

	const float xPos{ pos.x + m_button.getGlobalBounds().width / 2.0f - m_text.getGlobalBounds().width / 2.0f };
	const float yPos{ pos.y + m_button.getGlobalBounds().height / 2.0f - m_text.getGlobalBounds().height / 2.0f };

	m_text.setPosition({ xPos, yPos });
}

void Button::drawTo(sf::RenderWindow& window) const
{
	window.draw(m_button);
	window.draw(m_text);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const
{
	const float mouseX = static_cast<float>(sf::Mouse::getPosition(window).x);
	const float mouseY = static_cast<float>(sf::Mouse::getPosition(window).y);

	const float btnPosX = m_button.getPosition().x;
	const float btnPosY = m_button.getPosition().y;

	const float btnxPosWidth = m_button.getPosition().x + m_button.getLocalBounds().width;
	const float btnyPosHeight = m_button.getPosition().y + m_button.getLocalBounds().height;

	if (mouseX >= btnxPosWidth || mouseX <= btnPosX || mouseY >= btnyPosHeight || mouseY <= btnPosY)
	{
		return false;
	}

	return true;
}