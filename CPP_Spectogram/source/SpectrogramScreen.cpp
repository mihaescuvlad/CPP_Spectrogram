#include "SpectrogramScreen.hpp"

SpectrogramScreen::SpectrogramScreen(const sf::Vector2f& screenSize, const sf::Vector2f& screenPos, unsigned charSize, const sf::Font& font, const SpriteButtonConfig& playPauseButton, const SpriteSliderConfig& volumeSlider, const ThemeManager& colorTheme)
  : m_colorTheme{ colorTheme },
  m_playPauseButton{ playPauseButton.m_size, {}, {}, {playPauseButton.m_sprite_color} },
  m_volumeSlider{volumeSlider.sliderSize, volumeSlider.sliderBarTexture, volumeSlider.sliderWheelTexture}
{
  updateTheme();
  m_sound.setBuffer(m_soundBuffer);
  m_sound.setLoop(true);

  m_screenBackground.setSize(screenSize);
  m_screenBackground.setPosition(screenPos);

  const float volumeSliderPosX = screenPos.x + m_screenBackground.getGlobalBounds().width - volumeSlider.sliderSize.x - 25.0f;
  const float volumeSliderPosY = screenPos.y + screenSize.y - 75.0f;
  m_volumeSlider.setPosition({ volumeSliderPosX, volumeSliderPosY });

  const sf::Vector2f innerScreenSize{screenSize.x - 24.0f, screenSize.y - 125.0f};
  const sf::Vector2f innerScreenPos{ screenPos.x + 12.0f, screenPos.y + 25.0f};

  m_innerScreen.setSize(innerScreenSize);
  m_innerScreen.setPosition(innerScreenPos);

  m_isPlayingStatus = false;

  m_noFileSelectedText.setString("No File Selected");
  m_noFileSelectedText.setCharacterSize(charSize);
  m_noFileSelectedText.setFont(font);

  const float xPos{ screenPos.x + m_screenBackground.getGlobalBounds().width / 2.0f - m_noFileSelectedText.getGlobalBounds().width / 2.0f };
  const float yPos{ screenPos.y + m_screenBackground.getGlobalBounds().height / 2.0f - m_noFileSelectedText.getGlobalBounds().height / 2.0f };

  m_noFileSelectedText.setPosition({ xPos, yPos });

  m_playPauseButton.setPosition({ (screenPos.x + screenSize.x) / 2.0f, screenPos.y + screenSize.y - 75.0f });
}

void SpectrogramScreen::updateBackgroundColor(const sf::Color& color)
{
  m_screenBackground.setFillColor(color);
}

void SpectrogramScreen::updateTextColor(const sf::Color& color)
{
  m_noFileSelectedText.setFillColor(color);
}

void SpectrogramScreen::updatePlayIcon(const sf::Texture icon)
{
  m_playPauseButton.setSpriteTexture(icon);
}

void SpectrogramScreen::setFilePath(const std::filesystem::path filePath)
{
  m_fileToPlay = filePath;
  m_noFileSelectedText.setString("");

  m_soundBuffer.loadFromFile(m_fileToPlay.string());
}

void SpectrogramScreen::setPlayButtonColor(const sf::Color& color)
{
  m_playPauseButton.setBackColor(color);
}

void SpectrogramScreen::updateTheme()
{
  m_screenBackground.setFillColor(m_colorTheme.getPButtonColor());
  m_innerScreen.setFillColor(m_colorTheme.getScreenColor());
  m_noFileSelectedText.setFillColor(m_colorTheme.getTextColor());
  m_playPauseButton.setBackColor(m_colorTheme.getPButtonColor());

  const std::vector<std::string> iconPaths = m_themeIcons.at(m_colorTheme.getCurrentTheme());
  m_playPauseButtonTexture.loadFromFile(iconPaths.at(m_isPlayingStatus));
  m_playPauseButton.setSpriteTexture(m_playPauseButtonTexture);

  auto& [sliderBarTexture, sliderWheelTexture] = m_sliderTextures;
  sliderBarTexture.loadFromFile(iconPaths.at(2));
  sliderWheelTexture.loadFromFile(iconPaths.at(3));
  m_volumeSlider.setTextures(sliderBarTexture, sliderWheelTexture);
}

void SpectrogramScreen::playAudio()
{
  m_sound.play();
}

bool SpectrogramScreen::isMouseOverPlayButton(const sf::RenderWindow& window) const
{
  return m_playPauseButton.isMouseOver(window);
}

void SpectrogramScreen::pressPlayButton()
{
  m_isPlayingStatus = !m_isPlayingStatus;
  updateTheme();

  if (!m_isPlayingStatus) {
    m_sound.stop();
    return;
  }

  playAudio();
}

void SpectrogramScreen::handleEvent(const sf::RenderWindow& window, const sf::Event& event)
{
  m_volumeSlider.handleEvent(window, event);

  switch (event.type)
  {
  case sf::Event::MouseMoved:
  {
    if (!m_volumeSlider.isBeingHeld()) break;

    m_sound.setVolume(m_volumeSlider.getSliderValue() * 100.0f);
    break;
  }
  case sf::Event::MouseButtonPressed:
    if (!isMouseOverPlayButton(window) || event.mouseButton.button == sf::Mouse::Right) break;
    pressPlayButton();
    break;
  }
}

void SpectrogramScreen::drawTo(sf::RenderWindow& window) const
{
  window.draw(m_screenBackground);
  if (m_noFileSelectedText.getString() != "") 
  {
    window.draw(m_noFileSelectedText);
  }
  else 
  {
    window.draw(m_innerScreen);
    m_playPauseButton.drawTo(window);
    m_volumeSlider.drawTo(window);
  }
}