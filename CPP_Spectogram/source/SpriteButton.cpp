#include "SpriteButton.hpp"

SpriteButton::SpriteButton(const sf::Vector2f& buttonSize, const sf::Color& bgColor, const sf::Texture& texture, const sf::Color& spriteColor, const sf::Vector2f& pos)
	: Button{buttonSize, bgColor}
{
	m_sprite.setTexture(texture);
	m_sprite.setColor(spriteColor);

	setPosition(pos);
}

void SpriteButton::setSpriteTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);

	int textureWidth = static_cast<int>(texture.getSize().x);
	int textureHeight = static_cast<int>(texture.getSize().y);

	m_sprite.setTextureRect({ 0, 0, textureWidth, textureHeight });
}

void SpriteButton::setSpriteColor(const sf::Color& color)
{
	m_sprite.setColor(color);
}

void SpriteButton::setPosition(const sf::Vector2f& pos)
{
	Button::setPosition(pos);

	const float xPos{ pos.x + m_button.getGlobalBounds().width / 2.0f - m_sprite.getGlobalBounds().width / 2.0f };
	const float yPos{ pos.y + m_button.getGlobalBounds().height / 2.0f - m_sprite.getGlobalBounds().height / 2.0f };

	m_sprite.setPosition({ xPos, yPos });
}

void SpriteButton::drawTo(sf::RenderWindow& window) const
{
	Button::drawTo(window);

	window.draw(m_sprite);
}