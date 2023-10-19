#include "Scoreboard.h"

void Scoreboard::initBackdround()
{
	if (!scoreBoardBackgroundTex.loadFromFile("Textures/bg1.png"))
	{
		std::cout << "can't open scoreboard backgriund" << std::endl;
	}
	this->scoreBoardBackground.setTexture(this->scoreBoardBackgroundTex);
}

void Scoreboard::initText()
{
	if (!font.loadFromFile("Fonts/Amatic-Bold.ttf"))
		std::cout << "Can't open font!";

	this->menu[0].setFont(font);
	this->menu[0].setPosition(300, 400);
	this->menu[0].setFillColor(sf::Color::White);
	this->menu[0].setCharacterSize(60);
	this->menu[0].setString("BACK   TO   MENU");
	this->menu[0].setOutlineThickness(2);
}

Scoreboard::Scoreboard()
{
	this->initBackdround();
	this->initText();
}

void Scoreboard::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	//draw

	window.draw(scoreBoardBackground);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Scoreboard::updateMouseInput(sf::RenderWindow& window)
{
	this->mousePosition = sf::Mouse::getPosition(window);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		this->mouseHolding[i] = false;
		if (menu[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
		{
			this->menu[i].setFillColor(sf::Color::Red);
			this->mouseHolding[i] = true;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (mouseHolding[0])
				{
					std::cout << "BACK   TO   MENU" << std::endl;
					this->gameStatus = "MainMenu";
				}
			}
		}
		else
			this->menu[i].setFillColor(sf::Color::White);
	}
}
