#ifndef CURRENT_FILE_TEXT_HPP
#define CURRENT_FILE_TEXT_HPP

#include <filesystem>
#include <SFML/Graphics.hpp>

class CurrentFileText
{
private:
  std::filesystem::path m_selectedFilePath;
  sf::Text m_selectedFileText;
public:
  CurrentFileText(unsigned charSize, const sf::Font& font, const sf::Color& textColor, const sf::Vector2f& pos = {});

  void setString(const std::string& text);
  void setTextColor(const sf::Color& color);
  void setPosition(const sf::Vector2f& pos);

  void drawTo(sf::RenderWindow& window) const;
};

#endif
