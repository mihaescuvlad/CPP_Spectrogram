#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "BasicFileManager.hpp"
#include "Button.hpp"
#include "Constants.hpp"
#include "FilesystemNav.hpp"
#include "GuiTheme.hpp"
#include "IFileManager.hpp"
#include "SpriteButton.hpp"
#include "TextButton.hpp"
#include "ThemeManager.hpp"
#include "CurrentFileText.hpp"
#include "SpectrogramScreen.hpp"
#include "SpriteSlider.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 800), "Basic Spectrogram");

	ThemeManager themeManager({ static_cast<float>(window.getSize().x - 75.0), 25 });

	sf::Font defaultFont;
	defaultFont.loadFromFile(Constants::DEFAULT_FONT);

	CurrentFileText workingFile(20, defaultFont, themeManager.getTextColor(), { 25.0, static_cast<float>(window.getSize().y - 50.0) });

	sf::Texture playPauseIcon;
	playPauseIcon.loadFromFile(Constants::LIGHT_THEME_ICON);

	sf::Texture slTest1;
	slTest1.loadFromFile(Constants::LIGHT_PLAYER_ICONS[2]);
	sf::Texture slTest2;
	slTest2.loadFromFile(Constants::LIGHT_PLAYER_ICONS[3]);
	SpriteSliderConfig volumeSliderConfig{ {200, 50}, slTest1, slTest2, {500, 500} };
	SpectrogramScreen spectrogramScreen{ {static_cast<float>(window.getSize().x) - 100.0f, static_cast<float>(window.getSize().y) - 200.0f}, {50, 100}, 45, defaultFont, {{50,50}, {}, {}}, volumeSliderConfig, themeManager };
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool displayNav = false;
	const sf::Vector2f navSize{ 500, 600 };
	const sf::Vector2f navPos{ 262, 100 };

	sf::Texture nextPageButtonIcon;
	nextPageButtonIcon.loadFromFile(Constants::LIGHT_THEME_ICON);
	const SpriteButtonConfig nextPageButton{ {50,50}, themeManager.getPButtonColor(), nextPageButtonIcon };

	sf::Texture prevPageButtonIcon;
	prevPageButtonIcon.loadFromFile(Constants::LIGHT_THEME_ICON);
	const SpriteButtonConfig prevPageButton{ {50,50}, themeManager.getPButtonColor(), prevPageButtonIcon };

	sf::Texture closeTabIcon;
	closeTabIcon.loadFromFile(Constants::LIGHT_THEME_ICON);
	const SpriteButtonConfig closeTab{ {50,50}, themeManager.getPButtonColor(), closeTabIcon };

	const NavDetailsConfig navDetails{ {{}, 15, defaultFont, Constants::LIGHT_TEXT}, { {}, 20, defaultFont, Constants::LIGHT_TEXT} };

	const TextButtonConfig optionConfig{ {449, 70}, {}, {}, 20, defaultFont, {}};

	FilesystemNav fileNav{ [] { return makeBasicFileManager(); }, themeManager.getCurrentTheme(), navSize, navPos,
	  nextPageButton, prevPageButton, closeTab,
	  navDetails, optionConfig, {290, 195},
	  workingFile, spectrogramScreen, displayNav};

	fileNav.setControlsPosition({ 612, 625 }, { 362, 625 }, {689, 125});
	fileNav.setDetailsPosition({292, 140 }, {492, 635});
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TextButton selectFileButton({ 125, 50 }, themeManager.getPButtonColor(), "Select File", 20, defaultFont, themeManager.getTextColor(), { 25, 25 });

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			themeManager.update(window);

			if (selectFileButton.isMouseOver(window))
			{
				selectFileButton.setBackColor(themeManager.getAccentColor());
			}
			else
			{
				selectFileButton.setBackColor(themeManager.getPButtonColor());
			}

			if (displayNav)
			{
				if (fileNav.isMouseOverNextPage(window)){}
				if (fileNav.isMouseOverPrevPage(window)){}
				if (fileNav.isMouseOverCloseTab(window)){}
				if (fileNav.isMouseOverOption(window)){}
			}

			spectrogramScreen.handleEvent(window, event);
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Right) break;

				if(themeManager.isMouseOver(window))
				{
std::cerr << "Log: [Clicked] - Swap_Theme\n";
					themeManager.swapTheme();

					selectFileButton.setTextColor(themeManager.getTextColor());
					workingFile.setTextColor(themeManager.getTextColor());

					fileNav.setTheme(themeManager.getCurrentTheme());
					spectrogramScreen.updateTheme();
				}

				if(selectFileButton.isMouseOver(window))
				{
std::cerr << "Log: [Clicked] - Select_File\n";
					displayNav = true;
				}

				if(displayNav)
				{
					if(fileNav.isMouseOverNextPage(window))
					{
std::cerr << "Log: [Clicked] - Next_Page\n";
						fileNav.pressNextPage();
					}

					if(fileNav.isMouseOverPrevPage(window))
					{
std::cerr << "Log: [Clicked] - Previous_Page\n";
						fileNav.pressPrevPage();
					}

					if (fileNav.isMouseOverCloseTab(window)) 
					{
std::cerr << "Log: [Clicked] - Close_Tab\n";
						displayNav = false;
						fileNav.pressCloseTab();
					}

					if (fileNav.isMouseOverOption(window))
					{
std::cerr << "Log: [Clicked] - Option\n";
						fileNav.pressOption(window);
					}
				}
				break;
			default:
				break;
			}
		}

		window.clear(themeManager.getBackgroundColor());
		selectFileButton.drawTo(window);
		workingFile.drawTo(window);
		themeManager.drawTo(window);
		spectrogramScreen.drawTo(window);

		if (displayNav) 
		{
			fileNav.drawTo(window);
		}

		window.display();
	}

	return 0;
}
