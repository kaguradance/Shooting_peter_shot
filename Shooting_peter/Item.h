#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>

enum ItemType {
    HEART,
    MAGAZINE
};

class Item
{
private:
    sf::Texture texture;

    float speed;
    ItemType type;

    void initVariables();

    void initTexture();
    void initSprite();

public:
    Item(float pos_x, float pos_y, ItemType itemType);
    virtual ~Item();
    sf::Sprite sprite;

    //Accession
    const sf::FloatRect getBounds() const;
    ItemType getType() const;

    //Function
    void update();
    void render(sf::RenderTarget* target);
};

#endif //!ITEM_H