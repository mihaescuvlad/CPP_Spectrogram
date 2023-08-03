#include "Constants.hpp"

const std::filesystem::path Constants::DEFAULT_FILE_PATH					= "input_data";

const sf::Color Constants::LIGHT_TEXT															= { 7, 7, 9 };
const sf::Color Constants::LIGHT_BACKGROUND												= { 206, 206, 214 };//{ 232, 233, 237 };
const sf::Color Constants::LIGHT_PRIMARY_BUTTON										= { 185, 186, 191 };//{ 210, 211, 219 };
const sf::Color Constants::LIGHT_SECONDARY_BUTTON									= { 164, 164, 171 };//{ 194, 178, 181 };
const sf::Color Constants::LIGHT_SCREEN														= { 118, 118, 136 };//{ 179, 179,179 };
const sf::Color Constants::LIGHT_ACCENT														= { 136, 136, 151 };//{ 204, 206, 215 };

const sf::Color Constants::DARK_TEXT															= { 252, 252, 253 };
const sf::Color Constants::DARK_BACKGROUND												= { 16, 17, 19 };
const sf::Color Constants::DARK_PRIMARY_BUTTON										= { 89, 95, 105 };
const sf::Color Constants::DARK_SECONDARY_BUTTON									= { 43, 45, 49 };
const sf::Color Constants::DARK_SCREEN														= { 24, 24, 27 };
const sf::Color Constants::DARK_ACCENT														= { 130, 136, 179 };

const std::string Constants::DEFAULT_FONT													= "resources\\fonts\\cambriab.ttf";
const sf::Color Constants::DEFAULT_ICON_COLOR											= { 255, 255, 255, 200 };

const std::string Constants::LIGHT_THEME_ICON											= "resources\\images\\LightThemeIcon.png";
const std::string Constants::DARK_THEME_ICON											= "resources\\images\\DarkThemeIcon.png";

const std::vector<std::string> Constants::LIGHT_NAV_ICONS			= {	"resources\\images\\LightThemeNextButtonIcon.png",
                                                                        "resources\\images\\LightThemePrevButtonIcon.png",
																	                                      "resources\\images\\LightThemeCloseTabIcon.png" };

const std::vector<std::string> Constants::DARK_NAV_ICONS			= { "resources\\images\\DarkThemeNextButtonIcon.png",
																																				"resources\\images\\DarkThemePrevButtonIcon.png",
																																				"resources\\images\\DarkThemeCloseTabIcon.png" };

const std::vector<std::string> Constants::LIGHT_PLAYER_ICONS	=	{ "resources\\images\\LightThemePlayButton.png",
																																				"resources\\images\\LightThemePauseButton.png",
                                                                        "resources\\images\\LightVolumeSlider.png",
																																				"resources\\images\\LightVolumeSliderWheel.png"};

const std::vector<std::string> Constants::DARK_PLAYER_ICONS		= { "resources\\images\\DarkThemePlayButton.png",
																																				"resources\\images\\DarkThemePauseButton.png",
																																				"resources\\images\\DarkVolumeSlider.png",
																																				"resources\\images\\DarkVolumeSliderWheel.png"};

const unsigned Constants::MAX_NAV_ELEMENT_COUNT										= 5;
const uint32_t Constants::MAX_CHARACTERS_PER_ROW									= 30;
const uint32_t Constants::MAX_CHARACTERS_TIL_ELLIPSING						= 57;
const uint32_t Constants::MAX_PATH_LENGTH													= 47;

const std::unordered_set<std::string> Constants::SUPPORTED_FILE_EXTENSIONS = {
																																	".wav", ".aifc", ".snd", ".raw", ".paf", ".svx", ".sf", ".voc", ".w64",
																																	".mat4", ".mat5", ".pvf", ".xi", ".htk", ".caf", ".sd2", ".flac", ".mp3"
																													};
