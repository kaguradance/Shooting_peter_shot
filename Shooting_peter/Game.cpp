#include "Game.h"

//private function
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 800), "Shooting! Peter! Shot!", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGUI()
{
	if (!this->font.loadFromFile("Fonts/Amatic-Bold.ttf"))
		std::cout << "ERROR Fonts Fail" << "\n";
	this->pointText.setPosition(680.f, 10.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(36);
	this->pointText.setFillColor(sf::Color::White);

	this->pointMaxText.setPosition(680.f, 50.f);
	this->pointMaxText.setFont(this->font);
	this->pointMaxText.setCharacterSize(36);
	this->pointMaxText.setFillColor(sf::Color::White);

	this->hpText.setFont(this->font);
	this->hpText.setPosition(20.f, 50.f);
	this->hpText.setCharacterSize(36);
	this->hpText.setFillColor(sf::Color::White);

	this->hpMaxText.setFont(this->font);
	this->hpMaxText.setPosition(20.f, 90.f);
	this->hpMaxText.setCharacterSize(36);
	this->hpMaxText.setFillColor(sf::Color::White);

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(70);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Magenta);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/BGgameplay.png"))
	{
		std::cout << "ERROR BG" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);

	if (!this->endgameBGTex.loadFromFile("Textures/BGendgame.png"))
		std::cout << "ERROR endgameBG" << endl;
	this->endgameBG.setTexture(this->endgameBGTex);

}

void Game::initSystems()
{

}

void Game::initplayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
	this->countSpwanTimer = 0.2f;
}

void Game::initItems()
{
	this->spawnTimerMaxItemHeart = 200;
	this->spawnTimerItemHeart = this->spawnTimerMaxItemHeart;
	this->countSpwanTimerItemHeart = 0.1f;

	this->spawnTimerMaxItemMagazine = 300;
	this->spawnTimerItemMagazine = this->spawnTimerMaxItemMagazine;
	this->countSpwanTimerItemMagazine = 0.1f;
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initSystems();
	this->initplayer();
	this->initItems();
	this->initEnemies();
	this->initGUI();
	this->initWorld();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Deleate texture
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	for (auto* i : this->bullets)
	{
		delete i;
	}

	for (auto* i : this->items)
	{
		delete i;
	}

	for (auto* i : this->enemies)
	{
		delete i;
	}
}

//Function
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvent();

		if(this->player->getHp() > 0 && this->points >= 0)
			this->update();

		this->render();
	}
}

int Game::getPoint()
{
	return this->pointMax;
}

void Game::updatePollEvent()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
		if (this->player->getHp() <= 0 || this->points < 0)
		{
			if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Enter)
			{
				//std::cout << "Enter pressed!" << std::endl;
				this->player->setHp(5);
				this->player->setHpMax(5);
				this->points = 0;
				this->countSpwanTimer = 0.2f;
				this->countSpwanTimerItemHeart = 0.1f;
				for (auto* enemy : this->enemies)
				{
					delete enemy;
				}
				for (auto* item : this->items)
				{
					delete item;
				}
				this->enemies.clear();
				this->items.clear();
				this->counter = 0;
				this->counterItems = 0;
				this->window->close();
			}
		}
	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f - 8.f,
				this->player->getPos().y,
				0.f,
				-1.f,
				3.f
			)
		);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Point : " << this->points;
	this->pointText.setString(ss.str());

	std::stringstream sss;
	sss << "Score : " << this->pointMax;
	this->pointMaxText.setString(sss.str());

	std::stringstream sshp;
	sshp << "HP : " << this->player->getHp();
	this->hpText.setString(sshp.str());

	std::stringstream sshpmax;
	sshpmax << "HP MAX : " << this->player->getHpMax();
	this->hpMaxText.setString(sshpmax.str());

	//update player GUI
	float hpPercent = static_cast<float> (this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//left
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//right
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//top
	if (this->player->getBounds().top < this->window->getSize().y / static_cast<float>(2))
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y / static_cast<float>(2));
	}
	//botton
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y - 20.f)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - 20.f - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Game::updateEnemies()
{
	//spawning
	this->spawnTimer += countSpwanTimer; //spawn time
	if (this->spawnTimer >= spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(70.f + rand() % this->window->getSize().x - 70.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//count spawning time Enemy
	if (timerEnemy.getElapsedTime().asSeconds() >= 15.f) {
		countSpwanTimer += 0.05f;
		timerEnemy.restart();
	}

	//update
	counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//enemy culling
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//delate enemy
			delete this->enemies.at(counter);
			points -= 1;
			this->enemies.erase(this->enemies.begin() + counter);
		}

		//enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			//this->player->loseHp(1);
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}

		++counter;
	}
}

void Game::updateItems()
{
	this->spawnTimerItemHeart += countSpwanTimerItemHeart; //spawn time

	//spawning item
	if (this->spawnTimerItemHeart >= spawnTimerMaxItemHeart)
	{
		this->items.push_back(new Item(rand() % this->window->getSize().x - 20.f, -100.f, ItemType::HEART));
		this->spawnTimerItemHeart = 0.f;
	}

	//count spawning time item
	if (timerItem.getElapsedTime().asSeconds() >= 23.f) {
		countSpwanTimerItemHeart += 0.05f;
		timerItem.restart();
	}
	
	//update item
	counterItems = 0;
	for (auto* item : this->items)
	{
		item->update();

		//item  culling
		if (item->getBounds().left + item->getBounds().width < 10.f)
		{
			//Delete item
			delete this->items.at(counterItems);
			this->items.erase(this->items.begin() + counterItems);
		}

		//Item player collision
		else if (item->getBounds().intersects(this->player->getBounds()))
		{
			//std::cout << "Player collected an item!" << std::endl;

			switch (item->getType())
			{
			case HEART:
				this->player->gainHeart(item->getType());
				break;
			}
			delete this->items.at(counterItems);
			this->items.erase(this->items.begin() + counterItems);
		}
		++counterItems;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (i  < this->enemies.size() && this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();
				if (pointMax == points-1)
				{
					this->pointMax += 1;
				}
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted == true;
			}
		}
	}
}

void Game::update()
{
		this->updateInput();
		this->updateWorld();
		this->player->update();
		this->updateCollision();
		this->updateBullets();
		this->updateEnemies();
		this->updateItems();
		this->updateCombat();
		this->updateGUI();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->pointMaxText);
	this->window->draw(this->hpText);
	this->window->draw(this->hpMaxText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		//std::cout << "Enemies position: " << enemy->getBounds().left << ", " << enemy->getBounds().top << std::endl;
		enemy->render(this->window);
	}

	for (auto* item : this->items)
	{
		//item->update();
		// std::cout << "Item position: " << item->sprite.getPosition().x << ", " << item->sprite.getPosition().y<< std::endl;
		item->render(this->window);
	}

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0 || this->points < 0)
	{
		this->window->draw(this->endgameBG);
		this->window->draw(this->gameOverText);
	}

	this->window->display();

}
