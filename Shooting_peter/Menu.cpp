#include "Menu.h"
#include <SFML/Graphics.hpp>

Menu::Menu(float width, float height)
{
    font.loadFromFile("Fonts/Amatic-Bold.ttf");

    //play
    mainmenu[0].setFont(font);
    mainmenu[0].setFillColor(Color::Cyan);
    mainmenu[0].setString("PLAY");
    mainmenu[0].setOutlineThickness(3);
    mainmenu[0].setCharacterSize(70);
    mainmenu[0].setPosition(360, 350);

    //scoreboard
    mainmenu[1].setFont(font);
    mainmenu[1].setFillColor(Color::Cyan);
    mainmenu[1].setString("SCOREBOARD");
    mainmenu[1].setOutlineThickness(3);
    mainmenu[1].setCharacterSize(70);
    mainmenu[1].setPosition(300, 450);

    //Exit
    mainmenu[2].setFont(font);
    mainmenu[2].setFillColor(Color::Cyan);
    mainmenu[2].setString("EXIT");
    mainmenu[2].setOutlineThickness(3);
    mainmenu[2].setCharacterSize(70);
    mainmenu[2].setPosition(Vector2f(360, 550));

    selected = 0;
}

Menu::~Menu() {}

void Menu::setSelected(int n)
{
    selected = n;
}

void Menu::draw(RenderWindow& window)
{
    for (int i = 0; i < 3; i++) {
        window.draw(mainmenu[i]);
    }
}

void Menu::MoveDown()
{
    if (selected + 1 <= 3) //not exit
    {
        mainmenu[selected].setFillColor(Color::Cyan);
        selected++;
        if (selected == 3) {
            selected = 0;
        }
        mainmenu[selected].setFillColor(Color::Magenta);
    }
}

void Menu::MoveUp()
{
    if (selected - 1 >= -1) // not play
    {
        mainmenu[selected].setFillColor(Color::Cyan);
        selected--;
        if (selected == -1) {
            selected = 2;
        }
        mainmenu[selected].setFillColor(Color::Magenta);
    }
}