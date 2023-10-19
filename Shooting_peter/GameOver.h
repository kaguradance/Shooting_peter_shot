#pragma once

#define MAX_NUMBER_OF_ITEMS 1
#include <SFML/Graphics.hpp>
#include <iostream>

class GameOver
{
private:
	sf::Texture nameBackgroundTex;
	sf::Sprite nameBackground;

	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Vector2i mousePosition;

	bool mouseHolding[MAX_NUMBER_OF_ITEMS];

	void initBackground();
	void initText();

public:
	GameOver();
	void draw(sf::RenderWindow& window);
	void updateMouseInput(sf::RenderWindow& window);
	std::string gameStatus;
};

