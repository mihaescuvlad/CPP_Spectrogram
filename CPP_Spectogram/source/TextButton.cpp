#include "TextButton.hpp"

#include "Constants.hpp"

TextButton::TextButton(const sf::Vector2f& buttonSize, const sf::Color& bgColor, const std::string& text, const unsigned charSize, const sf::Font& font, const sf::Color& textColor)
: Button{ buttonSize, bgColor }
{
	m_text.setString(text);
	m_text.setCharacterSize(charSize);
	m_text.setFont(font);
	m_text.setFillColor(textColor);
}

void TextButton::setString(const std::string& text)
{
	m_text.setString(text);
}

void TextButton::setCharacterSize(const unsigned charSize)
{
	m_text.setCharacterSize(charSize);
}

void TextButton::setFont(const sf::Font& font)
{
	m_text.setFont(font);
}

void TextButton::setTextColor(const sf::Color& color)
{
	m_text.setFillColor(color);
}

void TextButton::setPosition(const sf::Vector2f& pos)
{
	Button::setPosition(pos);

	const float xPos{ pos.x + m_button.getGlobalBounds().width / 2.0f - m_text.getGlobalBounds().width / 2.0f };
	const float yPos{ pos.y + m_button.getGlobalBounds().height / 2.0f - m_text.getGlobalBounds().height / 2.0f };
	
	m_text.setPosition({ xPos, yPos });
}

std::string TextButton::getString() const
{
	return m_text.getString();
}

void TextButton::drawTo(sf::RenderWindow& window) const
{
	Button::drawTo(window);

	window.draw(m_text);
}