#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <SFML/Graphics.hpp>

class SpriteSlider
{
protected:
  sf::Sprite m_slideBar;
  sf::Sprite m_slideWheel;

  float m_sliderValue{1.0};
  std::pair<int, int> m_permittedRange;

  bool m_isHeld{};

  float getBarWidth() const;
  float getBarHeight() const;
  float getWheelWidth() const;
  float getWheelHeight() const;
  void setWorkingRange();
public:
  SpriteSlider(const sf::Vector2f& sliderSize, const sf::Texture& sliderBarTexture, const sf::Texture& sliderWheelTexture, const sf::Vector2f& pos = {});

  void setTextures(const sf::Texture& sliderBarTexture, const sf::Texture& sliderWheelTexture);
  void setPosition(const sf::Vector2f pos);
  float getSliderValue() const;

  bool isMouseOver(const sf::RenderWindow& window) const;
  bool isBeingHeld() const;
  void handleEvent(const sf::RenderWindow& window, const sf::Event& event);
  void drawTo(sf::RenderWindow& window) const;
};

struct SpriteSliderConfig {
  sf::Vector2f sliderSize;
  sf::Texture sliderBarTexture;
  sf::Texture sliderWheelTexture;
  sf::Vector2f pos = {};
};

#endif