#pragma once

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "Scoreboard.h"

enum class GameState
{
	MainMenu,
	Scoreboard,
	GamePlay,
	GameOver,
};

class Game
{
private:
	sf::Clock timer;

	sf::RenderWindow* window;

	std::map<sf::String, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;
	sf::Text pointMaxText;
	sf::Text gameOverText;
	sf::Text newGameText;
	sf::Text pointMaxtext;

	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	int points;
	int pointMax;

	unsigned counter = 0;

	Player* player;
	GameState gameState;
	MainMenu mainMenu;
	GameOver gameOver;
	Scoreboard scoreboard;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	float spawnTimer;
	float spawnTimerMax;
	float countSpwanTimer;

	std::vector<Enemy*> enemies;

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void initplayer();
	void initEnemies();


public:
	Game();
	virtual ~Game();

	//Functions
	void run();

	void updatePollEvent();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();

	void update();

	void renderGUI();
	void renderWorld();
	void render();
};
