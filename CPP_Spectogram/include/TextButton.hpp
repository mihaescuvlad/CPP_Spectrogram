#ifndef GUI_TEXT_BUTTON_HPP
#define GUI_TEXT_BUTTON_HPP

#include <SFML/Graphics/Text.hpp>

#include "Button.hpp"

class TextButton final : public Button
{
private:
	sf::Text m_text;

public:

	TextButton(const sf::Vector2f& buttonSize, const sf::Color& bgColor, const std::string& text, unsigned charSize, const sf::Font& font, const sf::Color& textColor);

	void setString(const std::string& text);
	void setCharacterSize(unsigned charSize);
	void setFont(const sf::Font& font);
	void setTextColor(const sf::Color& color);
	void setPosition(const sf::Vector2f& pos) override;

	void drawTo(sf::RenderWindow& window) const override;
};

struct TextButtonConfig {
	const sf::Vector2f& m_size;
	const sf::Color& m_bg_color;
	const std::string& m_text;
	const unsigned m_char_size;
	const sf::Font& m_font;
	const sf::Color& m_color;
};

#endif