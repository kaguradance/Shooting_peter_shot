#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;
	float currentShootingSpeed;

	int hp;
	int hpMax;

	//private functions
	void initVariables();
	void initTexture();
	void initSprite();
	
public:
	Player();
	virtual ~Player();

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//modofires
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void setHpMax(const int hpMax);
	void loseHp(const int value);

	void gainHeart(int hp);

	//Functions
	void move(const float dirX, const float dirY);
	const bool canAttack();

	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};
