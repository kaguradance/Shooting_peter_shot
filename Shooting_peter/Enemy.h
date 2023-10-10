#ifndef ENEMY_H
#define ENEMY_H
#include<SFML/Graphics.hpp>
#include<iostream>

class Enemy
{
private:
	unsigned pointCount;
	sf::Sprite shape;
	sf::Texture texture;

	float speed;
	int damage;
	int points;

	void initShape();
	void initVariables();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	void update();
	void render(sf::RenderTarget* target);
};

#endif //!ENEMY_H
