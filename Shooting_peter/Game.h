#pragma once

#include<map>
#include<string>
#include<sstream>
#include<SFML/Graphics.hpp>
#include<SFML/System/Clock.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

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
	sf::Text gameOverText;
	sf::Text newGameText;

	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	unsigned points;

	Player* player;

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
