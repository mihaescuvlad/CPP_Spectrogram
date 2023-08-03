#ifndef GUI_SPRITE_BUTTON_HPP
#define GUI_SPRITE_BUTTON_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Button.hpp"
#include "Constants.hpp"

class SpriteButton final : public Button
{
private:
	sf::Sprite m_sprite;

public:

	SpriteButton(const sf::Vector2f& buttonSize, const sf::Color& bgColor, const sf::Texture& texture, const sf::Color& spriteColor = Constants::DEFAULT_ICON_COLOR, const sf::Vector2f& pos = {});

	void setSpriteTexture(const sf::Texture& texture);
	void setSpriteColor(const sf::Color& color);
	void setPosition(const sf::Vector2f& pos) override;

	void drawTo(sf::RenderWindow& window) const override;
};

struct SpriteButtonConfig {
	sf::Vector2f m_size;
	sf::Color m_bg_color;
	sf::Texture m_texture;
	sf::Color m_sprite_color = Constants::DEFAULT_ICON_COLOR;
};

#endif