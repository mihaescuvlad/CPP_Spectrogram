
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

void initializeTestObject()
{

	const sf::Vector2f size{ 800, 600 };
	const sf::Color bgColor{ sf::Color::Cyan };
	const sf::Vector2f pos{ 200, 200 };

	sf::Texture nextPageButtonIcon;
	nextPageButtonIcon.loadFromFile(Constants::DARK_THEME_ICON);
	const SpriteButtonConfig nextPageButton{{50,50}, {sf::Color::Black}, nextPageButtonIcon };

	sf::Texture prevPageButtonIcon;
	prevPageButtonIcon.loadFromFile(Constants::LIGHT_THEME_ICON);
	const SpriteButtonConfig prevPageButton{ {50,50}, {sf::Color::Red}, prevPageButtonIcon };

	sf::Texture closeTabIcon;
	closeTabIcon.loadFromFile(Constants::LIGHT_THEME_ICON);
	const SpriteButtonConfig closeTab{ {50,50}, {sf::Color::Blue}, closeTabIcon };

	sf::Font defaultFont;
	defaultFont.loadFromFile(Constants::DEFAULT_FONT);
	const NavDetailsConfig navDetails{ {"Select File", 20, defaultFont, Constants::LIGHT_TEXT}, { {}, 20, defaultFont, Constants::LIGHT_TEXT} };

	FilesystemNav obj{ [] { return makeBasicFileManager(); }, size, bgColor, pos, nextPageButton, prevPageButton, closeTab, navDetails};

	int a = 3, b = 5;

	int res = a + b;
	res++;
}

int main()
{
	initializeTestObject();

	sf::RenderWindow window(sf::VideoMode(1024, 800), "Basic Spectrogram");

	ThemeManager themeManager({ static_cast<float>(window.getSize().x - 75.0), 25 });

	sf::Font defaultFont;
	defaultFont.loadFromFile(Constants::DEFAULT_FONT);

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
				}

				if(selectFileButton.isMouseOver(window))
				{
std::cerr << "Log: [Clicked] - Select_File\n";
				}
				break;
			default:
				break;
			}
		}

		window.clear(themeManager.getBackgroundColor());
		selectFileButton.drawTo(window);
		themeManager.drawTo(window);
		window.display();
	}

	return 0;
}
