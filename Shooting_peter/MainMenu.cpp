#include "MainMenu.h"

void MainMenu::initBackground()
{
	if (!menuBackgroundTex.loadFromFile("Textures/BGmenu.png"))
	{
		std::cout << "Can't open" << std::endl;
	}
	this->menuBackground.setTexture(this->menuBackgroundTex);
}

void MainMenu::initText()
{
	if (!font.loadFromFile("Fonts/Amatic-Bold.ttf"))
		std::cout << "Can't open font!";

	this->menu[0].setFont(font);
	this->menu[0].setString("Start");
	this->menu[0].setFillColor(sf::Color::White);
	this->menu[0].setCharacterSize(70);
	this->menu[0].setOutlineThickness(1.5);
	this->menu[0].setPosition(sf::Vector2f(100, 250));

	this->menu[1].setFont(font);
	this->menu[1].setString("Scoreboard");
	this->menu[1].setFillColor(sf::Color::White);
	this->menu[1].setCharacterSize(70);
	this->menu[1].setOutlineThickness(1.5);
	this->menu[1].setPosition(sf::Vector2f(100, 350));

	this->menu[2].setFont(font);
	this->menu[2].setString("Exit");
	this->menu[2].setFillColor(sf::Color::White);
	this->menu[2].setCharacterSize(70);
	this->menu[2].setOutlineThickness(1.5);
	this->menu[2].setPosition(sf::Vector2f(100, 450));

	this->devName.setFont(font);
	this->devName.setString("Pimsirin        Suwannabut        66010575");
	this->devName.setFillColor(sf::Color::Yellow);
	this->devName.setCharacterSize(40);
	this->devName.setOutlineThickness(1);
	this->devName.setPosition(sf::Vector2f(20, 750));

	this->gameName.setFont(font);
	this->gameName.setString("Shooting!     Peter!    Shot!");
	this->gameName.setFillColor(sf::Color::Magenta);
	this->gameName.setCharacterSize(90);
	this->gameName.setOutlineThickness(2);
	this->gameName.setPosition(sf::Vector2f(100, 50));
}

MainMenu::MainMenu()
{
	this->initText();
	this->initBackground();
}

void MainMenu::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	//window.draw(menu);

	window.draw(menuBackground);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}

	window.draw(devName);
	window.draw(gameName);
}

void MainMenu::updateMouseInput(sf::RenderWindow& window)
{
	this->mousePosition = sf::Mouse::getPosition(window);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		this->mouseHoding[i] = false;
		if (menu[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
		{
			this->menu[i].setFillColor(sf::Color::Red);
			this->mouseHoding[i] = true;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (mouseHoding[0])
				{
					std::cout << "Start Game" << std::endl;
					this->gameStatus = "Start";
				}
				else if (mouseHoding[1])
				{
					std::cout << "Scoreboard" << std::endl;
					this->gameStatus = "Scoreboard";
				}
				else if (mouseHoding[2])
				{
					std::cout << "Exit" << std::endl;
					window.close();
				}
			}
		}
		else
			this->menu[i].setFillColor(sf::Color::White);
	}
}


