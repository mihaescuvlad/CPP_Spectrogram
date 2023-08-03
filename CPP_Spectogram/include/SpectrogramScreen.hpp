#ifndef SPECTROGRAM_SCREEN_HPP
#define SPECTROGRAM_SCREEN_HPP

#include <vector>
#include <string>
#include "SpriteButton.hpp"
#include "SpriteSlider.hpp"
#include "ThemeManager.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class SpectrogramScreen
{
private:
  const ThemeManager& m_colorTheme;
  std::unordered_map<GuiTheme::Themes, std::vector<std::string>> m_themeIcons{
    { GuiTheme::Themes::LIGHT, Constants::LIGHT_PLAYER_ICONS },
    { GuiTheme::Themes::DARK, Constants::DARK_PLAYER_ICONS },
    { GuiTheme::Themes::INVALID_THEME, {} }
  };
  sf::Texture m_playPauseButtonTexture;
  std::pair<sf::Texture, sf::Texture> m_sliderTextures;

  std::filesystem::path m_fileToPlay;
  sf::SoundBuffer m_soundBuffer;
  sf::Sound m_sound;

  sf::RectangleShape m_screenBackground;
  sf::RectangleShape m_innerScreen;
  SpriteButton m_playPauseButton;
  SpriteSlider m_volumeSlider;

  bool m_isPlayingStatus;
  sf::Text m_noFileSelectedText;

  void updateBackgroundColor(const sf::Color& color);
  void updateTextColor(const sf::Color& color);
  void updatePlayIcon(const sf::Texture icon);

  void playAudio();
  bool isMouseOverPlayButton(const sf::RenderWindow& window) const;
  void pressPlayButton();
public:
  SpectrogramScreen(const sf::Vector2f& screenSize, const sf::Vector2f& screenPos, unsigned charSize, const sf::Font& font, const SpriteButtonConfig& playPauseButton, const SpriteSliderConfig& volumeSlider, const ThemeManager& colorTheme);

  void setFilePath(const std::filesystem::path filePath);
  void setPlayButtonColor(const sf::Color& color);

  
  void handleEvent(const sf::RenderWindow& window, const sf::Event& event);

  void updateTheme();
  void drawTo(sf::RenderWindow& window) const;
};

#endif