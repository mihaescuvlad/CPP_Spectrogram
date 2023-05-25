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


int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 800), "Basic Spectrogram");

	ThemeManager themeManager({ static_cast<float>(window.getSize().x - 75.0), 25 });

	sf::Font defaultFont;


	defaultFont.loadFromFile(Constants::DEFAULT_FONT);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const sf::Vector2f size{ 500, 600 };
	const sf::Vector2f pos{ 262, 100 };

	sf::Texture nextPageButtonIcon;
	nextPageButtonIcon.loadFromFile(Constants::LIGHT_THEME_ICON);
	const SpriteButtonConfig nextPageButton{ {50,50}, themeManager.getPButtonColor(), nextPageButtonIcon };

	sf::Texture prevPageButtonIcon;
	prevPageButtonIcon.loadFromFile(Constants::LIGHT_THEME_ICON);
	const SpriteButtonConfig prevPageButton{ {50,50}, themeManager.getPButtonColor(), prevPageButtonIcon };

	sf::Texture closeTabIcon;
	closeTabIcon.loadFromFile(Constants::DARK_THEME_ICON);
	const SpriteButtonConfig closeTab{ {50,50}, themeManager.getPButtonColor(), closeTabIcon };

	const NavDetailsConfig navDetails{ {{}, 15, defaultFont, Constants::LIGHT_TEXT}, { {}, 20, defaultFont, Constants::LIGHT_TEXT} };

	//FilesystemNav testObj{ [] { return makeBasicFileManager(); }, size, bgColor, pos, nextPageButton, prevPageButton, closeTab, navDetails };

	const TextButtonConfig optionConfig{ {449, 70}, {}, {}, 20, {defaultFont}, {}};

	FilesystemNav testObj{ [] { return makeBasicFileManager(); }, themeManager.getCurrentTheme(), size, pos, nextPageButton, prevPageButton, closeTab, navDetails, optionConfig, {290, 195} };
	//{362, 625}
	//{612, 625}
	testObj.setControlsPosition({ 612, 625 }, { 362, 625 }, {689, 125});
	testObj.setDetailsPosition({292, 140 }, {492, 635});
	bool displayNav = false;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TextButton selectFileButton({ 125, 50 }, themeManager.getPButtonColor(), "Select File", 20, defaultFont, themeManager.getTextColor());
	selectFileButton.setPosition({ 25, 25 });

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
				if (testObj.isMouseOverNextPage(window)){}
				if (testObj.isMouseOverPrevPage(window)){}
				if (testObj.isMouseOverCloseTab(window)){}
				if (testObj.isMouseOverOption(window)){}
			}

			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				break;
			case sf::Event::MouseButtonPressed:
				if(themeManager.isMouseOver(window))
				{
std::cerr << "Log: [Clicked] - Swap_Theme\n";
					themeManager.swapTheme();

					selectFileButton.setTextColor(themeManager.getTextColor());
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					testObj.setTheme(themeManager.getCurrentTheme());
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}

				if(selectFileButton.isMouseOver(window))
				{
std::cerr << "Log: [Clicked] - Select_File\n";
					displayNav = true;
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(displayNav)
				{
					if(testObj.isMouseOverNextPage(window))
					{
std::cerr << "Log: [Clicked] - Next_Page\n";
						testObj.pressNextPage();
					}

					if(testObj.isMouseOverPrevPage(window))
					{
std::cerr << "Log: [Clicked] - Previous_Page\n";
						testObj.pressPrevPage();
					}

					if (testObj.isMouseOverCloseTab(window)) 
					{
std::cerr << "Log: [Clicked] - Close_Tab\n";
						displayNav = false;
						testObj.pressCloseTab();
					}

					if (testObj.isMouseOverOption(window))
					{
std::cerr << "Log: [Clicked] - Option\n";
						testObj.pressOption(window);
					}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				break;
			default:
				break;
			}
		}

		window.clear(themeManager.getBackgroundColor());
		selectFileButton.drawTo(window);
		themeManager.drawTo(window);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (displayNav) {
			testObj.drawTo(window);
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		window.display();
	}

	return 0;
}
