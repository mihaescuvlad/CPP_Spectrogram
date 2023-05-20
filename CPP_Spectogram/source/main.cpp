
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Button.hpp"
#include "Constants.hpp"
#include "GuiTheme.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 900), "Basic Spectrogram");
	GuiTheme guiTheme;

	sf::Font defaultFont, iconFont;
	defaultFont.loadFromFile(Constants::DEFAULT_FONT);
	iconFont.loadFromFile("resources\\fonts\\arial-unicode-ms.ttf");

	char32_t Icon = U'\U0001F319';

	Button changeThemeButton(sf::String(Icon), {50, 50}, 20, guiTheme.getPButtonColor(), guiTheme.getTextColor());
	changeThemeButton.setFont(iconFont);
	changeThemeButton.setPosition({ static_cast<float>(window.getSize().x - 75.0), 25 });

	Button selectFileButton("Select File", { 125, 50 }, 20, guiTheme.getPButtonColor(), guiTheme.getTextColor());
	selectFileButton.setFont(defaultFont);
	selectFileButton.setPosition( { 25, 25 } );

	while (window.isOpen())
	{

		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (changeThemeButton.isMouseOver(window))
			{
				changeThemeButton.setBackColor(guiTheme.getAccentColor());
			}
			else
			{
				changeThemeButton.setBackColor(guiTheme.getPButtonColor());
			}

			if (selectFileButton.isMouseOver(window))
			{
				selectFileButton.setBackColor(guiTheme.getAccentColor());
			}
			else
			{
				selectFileButton.setBackColor(guiTheme.getPButtonColor());
			}

			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				break;
			case sf::Event::MouseButtonPressed:
				if (changeThemeButton.isMouseOver(window))
				{
					std::cout << "[Clicked] - Change_Theme\n";
					guiTheme.SwapTheme();
				}

				if(selectFileButton.isMouseOver(window))
				{
					std::cout << "[Clicked] - Select_File\n";
				}
				break;
			default:
				break;
			}
		}

		window.clear(guiTheme.getBackgroundColor());
		selectFileButton.drawTo(window);
		changeThemeButton.drawTo(window);
		window.display();
	}

	return 0;
}
