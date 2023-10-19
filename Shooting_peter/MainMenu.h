#pragma once

#define MAX_NUMBER_OF_ITEMS 3
#include <SFML/Graphics.hpp>
#include <iostream>


class MainMenu

{
private:
	sf::Texture menuBackgroundTex;
	sf::Sprite menuBackground;

	sf::Font font;
	sf::Text devName;
	sf::Text gameName;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Vector2i mousePosition;

	bool mouseHoding[MAX_NUMBER_OF_ITEMS];

	void initBackground();
	void initText();

public:
	MainMenu();
	void draw(sf::RenderWindow& window);
	void updateMouseInput(sf::RenderWindow& window);
	std::string gameStatus;
};
