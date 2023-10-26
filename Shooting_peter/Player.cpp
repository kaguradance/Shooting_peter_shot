#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 3.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 5;
	this->hp = this->hpMax;

}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("Textures/peter.png"))
	{
		std::cout << "ERROR" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(3.f, 3.f);
	this->sprite.setPosition(200.f, 530.f);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::setHpMax(const int hpMax)
{
	this->hpMax = hpMax;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHeart(int heart)
{
	this->hp += heart;
	this->hpMax += heart;
	if (this->hp > 0)
		this->hp += 1;
	if (this->hpMax > 0)
		this->hpMax += 1;
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.2f;
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
