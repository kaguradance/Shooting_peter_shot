#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"
#include "Menu.h"
#include "Player.h"
#include <time.h>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace sf;

float width;
float height;

int pagenum;
int pointMax;
string name;

struct HistoryScore {
    std::string namelead;
    int scorelead = 0;
}H1;

bool compareScores(const HistoryScore& a, const HistoryScore& b) {
    return a.scorelead > b.scorelead;
}

void PName(RenderWindow& window, std::string& name);
void History(RenderWindow& window);

int main()
{
    pagenum = 1000;
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow window(VideoMode(800, 800), "Shooting! Peter! Shot!");
    Menu menu(800, 800);

    sf::Music BGM;
    if (!BGM.openFromFile("Sounds/BGM.mp3"))
        std::cout << "ERROR loading BGM" << endl;

    Texture mainmenubg;
    mainmenubg.loadFromFile("Textures/BGmenu.png"); //เติมพื้นหลัง
    Sprite bg;
    bg.setTexture(mainmenubg);
    string name;


    while (true) {
        BGM.setVolume(1000);
        BGM.play();
        BGM.setLoop(true);

        if (pagenum == 1000) {

            while (window.isOpen()) {
              
                Event event;
                while (window.pollEvent(event)) {

                    if (event.type == Event::Closed) {
                        window.close();
                        break;
                    }

                    if (event.type == Event::KeyPressed) {

                        if (event.key.code == Keyboard::W) {

                            menu.MoveUp();
                        }

                        if (event.key.code == Keyboard::S) {

                            menu.MoveDown();
                        }

                        if (event.key.code == Keyboard::Enter) {

                            if (menu.pressed() == 0) {

                                pagenum = 0;
                            }

                            if (menu.pressed() == 1 ) {
                                pagenum = 1;
                            }

                            if (menu.pressed() == 2) {
                                pagenum = -1;
                            }
                        }

                        if (event.key.code == Keyboard::BackSpace) {

                        }
                    }
                }

                window.clear();
                if (pagenum != 1000) {
                    break;
                }
                window.draw(bg);
                menu.draw(window);
                window.display();
            }
            if (pagenum == -1) {
                window.close();
                break;
            }

            if (pagenum == 0) {
                PName(window, name);
                window.close();
            }

            if (pagenum == 1 ) {
                History(window);
            }

            if (pagenum == 2) {
                Game game;
                game.run();

                pointMax = game.getPoint();
                std::ofstream offile;
                offile.open("Score/score.txt", std::ios::app);
                offile << name << "," << "*" << game.getPoint() << std::endl;
                offile.close();
            }
        }
        BGM.stop();
    };
    return 0;
}

void PName(RenderWindow& window, std::string& name)
{
    if (!name.empty()) {
        name.clear();
    }
    Texture background;
    background.loadFromFile("Textures/BGentername.png");
    Sprite bg;
    bg.setTexture(background);

    Font font;
    font.loadFromFile("Fonts/Amatic-Bold.ttf");
    Text t2;
    t2.setFont(font);
    t2.setCharacterSize(80);
    t2.setPosition(window.getSize().x / 2 - t2.getLocalBounds().width / 2, 350);
    t2.setFillColor(Color::Magenta);
    t2.setOutlineThickness(1.5f);
    t2.setOutlineColor(sf::Color::Cyan);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed()) {
                window.close();
            }
            if (event.type == Event::TextEntered) {
                if (name.size() < 15) {
                    name += static_cast<char>(event.text.unicode);

                    FloatRect textBounds = t2.getLocalBounds();
                    t2.setOrigin(textBounds.width / 2, 0);
                    t2.setPosition(window.getSize().x / 2, 180);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Backspace) && name.size() > 0) {
                name.resize(name.size() - 1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) && name.size() > 1) {
                pagenum = 2; //game win
                return;
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                pagenum = 1000;
                return;
            }
        }
        t2.setString(name);
        window.clear();
        window.draw(bg);
        window.draw(t2);
        window.display();
    }
}

void History(RenderWindow& window)
{
    Texture Scorebg;
    Scorebg.loadFromFile("Textures/BGscoreboard1.png");
    Sprite bg;
    bg.setTexture(Scorebg);

    Font font;
    font.loadFromFile("Fonts/Amatic-Bold.ttf");
    Text nametext("", font, 70);
    Text scoretext("", font, 70);

    vector <HistoryScore> pointMax;
    ifstream scorefile("Score/score.txt");
    if (scorefile.is_open()) {
        string line;
        while (getline(scorefile, line)) {
            size_t commaPos = line.find(",");
            size_t asteriskPos = line.find("*");
            if (commaPos != string::npos && asteriskPos != string::npos) {
                H1.namelead = line.substr(0, commaPos);
                H1.scorelead = stoi(line.substr(asteriskPos + 1));
                pointMax.push_back(H1); // Add the H1 instance to the scores vector
            }
        }
        scorefile.close();
    }
    else {
        std::cout << "ERROR: Could not open scores.txt for reading." << std::endl;
    }

    sort(pointMax.begin(), pointMax.end(), compareScores);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                pagenum = 1000;
                return;
            }
        }

        window.clear();
        window.draw(bg);

        for (int i = 0; i < min(5, static_cast<int>(pointMax.size())); ++i) {
            nametext.setString(pointMax[i].namelead);
            nametext.setFillColor(Color::Magenta);
            nametext.setOutlineThickness(1);
            nametext.setPosition(200, 200 + i * 100);

            scoretext.setString(to_string(pointMax[i].scorelead));
            scoretext.setFillColor(Color::Cyan);
            scoretext.setOutlineThickness(1);
            scoretext.setPosition(550, 200 + i * 100);
            scoretext.setOrigin(scoretext.getLocalBounds().width / 2, 0);

            window.draw(nametext);
            window.draw(scoretext);
        }

        window.display();
    }

}