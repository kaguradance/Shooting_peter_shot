#include "Enemy.h"

void Enemy::initShape()
{
	if (!this->texture.loadFromFile("Textures/big_demon_idle_anim_f0.png"))
	{
		std::cout << "ERROR lodeing ghost texture!" << "\n";
	}
	this->shape.setTexture(this->texture);
	this->shape.scale(2.5f, 2.5f);
}

void Enemy::initVariables()
{
	this->pointCount = 1;
	this->speedTimer = 0.1f;
	this->speed = 1;
	//this->speed = this->speedTimer;
	this->damage = this->pointCount;
	this->points = this->pointCount;
	this->pointMax = this->pointCount;
}

Enemy::Enemy(float pos_x,float pos_y)
{
	this->initShape();
	this->initVariables();

	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const int& Enemy::getPoints() const
{
	return this->points;
	return this->pointMax;
}

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
