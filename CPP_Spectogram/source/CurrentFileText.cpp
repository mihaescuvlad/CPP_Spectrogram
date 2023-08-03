#include "CurrentFileText.hpp"

CurrentFileText::CurrentFileText(const unsigned charSize, const sf::Font& font, const sf::Color& textColor, const sf::Vector2f& pos)
{
  m_selectedFileText.setString("Current Working File: ");
  m_selectedFileText.setCharacterSize(charSize);
  m_selectedFileText.setFont(font);
  m_selectedFileText.setFillColor(textColor);

  setPosition(pos);
}

void CurrentFileText::setString(const std::string& text)
{
  m_selectedFileText.setString("Current Working File: " + text);
}

void CurrentFileText::setTextColor(const sf::Color& color)
{
  m_selectedFileText.setFillColor(color);
}

void CurrentFileText::setPosition(const sf::Vector2f& pos)
{
  m_selectedFileText.setPosition(pos);
}

void CurrentFileText::drawTo(sf::RenderWindow & window) const
{
  window.draw(m_selectedFileText);
}