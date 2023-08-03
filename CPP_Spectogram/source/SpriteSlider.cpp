#include "SpriteSlider.hpp"

#include <iostream>

SpriteSlider::SpriteSlider(const sf::Vector2f& sliderSize, const sf::Texture& sliderBarTexture, const sf::Texture& sliderWheelTexture, const sf::Vector2f& pos)
{
  setTextures(sliderBarTexture, sliderWheelTexture);

  const float xBarScale{ sliderSize.x / static_cast<float>(sliderBarTexture.getSize().x) };
  const float yBarScale{ sliderSize.y / static_cast<float>(sliderBarTexture.getSize().y) };
  m_slideBar.setScale({ xBarScale, yBarScale });

  m_slideWheel.setScale({ yBarScale, yBarScale });

  setPosition(pos);
}

float SpriteSlider::getBarWidth() const
{
  return m_slideBar.getLocalBounds().getSize().x * m_slideBar.getScale().x;
}
float SpriteSlider::getBarHeight() const
{
  return m_slideBar.getLocalBounds().getSize().y * m_slideBar.getScale().y;
}
float SpriteSlider::getWheelWidth() const
{
  return m_slideWheel.getLocalBounds().getSize().x * m_slideWheel.getScale().x;
}
float SpriteSlider::getWheelHeight() const
{
  return m_slideWheel.getLocalBounds().getSize().y * m_slideWheel.getScale().y;
}

void SpriteSlider::setWorkingRange()
{
  const int wheelWidth{ static_cast<int>(getWheelWidth()) };

  m_permittedRange = { static_cast<int>(m_slideBar.getPosition().x + static_cast<int>(wheelWidth / 2)),
                          static_cast<int>(m_slideBar.getPosition().x + getBarWidth() - static_cast<int>(wheelWidth / 2))};
}

void SpriteSlider::setTextures(const sf::Texture& sliderBarTexture, const sf::Texture& sliderWheelTexture)
{
  m_slideBar.setTexture(sliderBarTexture);
  m_slideWheel.setTexture(sliderWheelTexture);
}

void SpriteSlider::setPosition(const sf::Vector2f pos)
{
  m_slideBar.setPosition(pos);

  const float xPos{ pos.x + getBarWidth() - getBarHeight()};
  const float yPos{ pos.y };
  m_slideWheel.setPosition({ xPos, yPos });

  setWorkingRange();
}

float SpriteSlider::getSliderValue() const
{
  return m_sliderValue;
}

bool SpriteSlider::isMouseOver(const sf::RenderWindow& window) const
{
  const float mouseX = static_cast<float>(sf::Mouse::getPosition(window).x);
  const float mouseY = static_cast<float>(sf::Mouse::getPosition(window).y);

  const float sliderPosX = m_slideBar.getPosition().x;
  const float sliderPosY = m_slideBar.getPosition().y;

  const float sliderXPosWidth = sliderPosX + getBarWidth();
  const float sliderYPosHeight = sliderPosY + getBarHeight();

  if (mouseX >= sliderXPosWidth || mouseX <= sliderPosX || mouseY >= sliderYPosHeight || mouseY <= sliderPosY)
  {
    return false;
  }

  return true;
}

bool SpriteSlider::isBeingHeld() const
{
  return m_isHeld;
}

void SpriteSlider::handleEvent(const sf::RenderWindow& window, const sf::Event& event)
{
  switch (event.type)
  {
  case sf::Event::MouseMoved:
  {
      if (!m_isHeld) break;

      auto [minRange, maxRange] = m_permittedRange;
      const int clippedMouseX = std::max(minRange, std::min(maxRange, sf::Mouse::getPosition(window).x));
      m_slideWheel.setPosition(static_cast<float>(clippedMouseX - (getWheelWidth() / 2.0)), m_slideWheel.getPosition().y);
      m_sliderValue = static_cast<float>(clippedMouseX - minRange) / static_cast<float>(maxRange - minRange);
    break;
  }
  case sf::Event::MouseButtonPressed:
      if (!isMouseOver(window) || event.mouseButton.button == sf::Mouse::Right) break;
std::cerr << "Log: [Clicked] - Sprite_Slider\n";
      m_isHeld = true;
    break;
  case sf::Event::MouseButtonReleased:
      if (event.mouseButton.button == sf::Mouse::Right) break;
      m_isHeld = false;
    break;
  }
}

void SpriteSlider::drawTo(sf::RenderWindow& window) const
{
  window.draw(m_slideBar);
  window.draw(m_slideWheel);
}