#pragma once

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Menu.h"
#include "Item.h"

class Game
{
private:
	sf::Clock timerEnemy;
	sf::Clock timerItem;

	sf::RenderWindow* window;

	std::map<sf::String, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	
	sf::Text pointText;
	sf::Text pointMaxText;

	sf::Text gameOverText;
	sf::Text newGameText;;

	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;
	sf::Texture endgameBGTex;
	sf::Sprite endgameBG;

	int points;
	int pointMax;
	int type;

	unsigned counter = 0;
	unsigned counterItems = 0;

	Player* player;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	float spawnTimer;
	float spawnTimerMax;
	float countSpwanTimer;
	std::vector<Enemy*> enemies;

	float spawnTimerItemHeart;
	float spawnTimerMaxItemHeart;
	float countSpwanTimerItemHeart;

	float spawnTimerItemMagazine;
	float spawnTimerMaxItemMagazine;
	float countSpwanTimerItemMagazine;

	bool itemSpawn = false;
	std::vector<Item*> items;

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void initplayer();
	void initEnemies();
	void initItems();

public:
	Game();
	virtual ~Game();

	//Functions
	void run();
	int getPoint();

	void updatePollEvent();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateItems();
	void updateCombat();

	void update();

	void renderGUI();
	void renderWorld();
	void render();
};
