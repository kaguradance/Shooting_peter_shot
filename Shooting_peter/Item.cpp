#include "Item.h"

void Item::initVariables()
{
    this->speed = 1.f;
}

void Item::initTexture()
{
    switch (this->type)
    {
    case HEART:
        if (!this->texture.loadFromFile("Textures/itemheart.png"))
        {
            std::cout << "ERROR::ItemHeart." << "\n";
        }
        break;
    }
}

void Item::initSprite()
{
    this->sprite.setTexture(this->texture);

    //resize
    this->sprite.setScale(1.3f, 1.3f);

}

Item::Item(float pos_x, float pos_y, ItemType itemType)
{
    this->type = itemType;

    this->initVariables();
    this->initTexture();
    this->initSprite();

    this->sprite.setPosition(pos_x, pos_y);
}

Item::~Item()
{

}

const sf::FloatRect Item::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

ItemType Item::getType() const
{
    return this->type;
}

void Item::update()
{
    this->sprite.move(0.f, this->speed);
}

void Item::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}