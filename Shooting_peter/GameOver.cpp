#include "GameOver.h"

void GameOver::initBackground()
{
	if (!nameBackgroundTex.loadFromFile("Textures/bg1.png"))
	{
		std::cout << "can't open enterNameBackground" << std::endl;
	}
	this->nameBackground.setTexture(this->nameBackgroundTex);
}

void GameOver::initText()
{
	if (!font.loadFromFile("Fonts/Amatic-Bold.ttf"))
		std::cout << "Can't open font!";

	this->menu[0].setFont(font);
	this->menu[0].setString("Enter");
	this->menu[0].setFillColor(sf::Color::White);
	this->menu[0].setCharacterSize(70);
	this->menu[0].setOutlineThickness(1.5);
	this->menu[0].setPosition(sf::Vector2f(350, 500));
}

GameOver::GameOver()
{
	this->initBackground();
	this->initText();
}

void GameOver::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	//draw

	window.draw(nameBackground);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}

}

void GameOver::updateMouseInput(sf::RenderWindow& window)
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
					std::cout << "Scoreboard" << std::endl;
					this->gameStatus = "Scoreboard";
				}
			}
		}
		else
			this->menu[i].setFillColor(sf::Color::White);
	}
}
