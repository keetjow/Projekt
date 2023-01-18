#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"

class Menu
{
private:
    sf::Sprite heart;
    sf::Texture heartTexture;
    bool firstGame = true;
    sf::Text statsTextScore;
    sf::Text statsTextTime;
    sf::Text statsTextEnemiesKilled;
    sf::Text statsTextProjectilesShot;
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text scoreText;
    sf::Text pause;
    sf::Text dead;
    sf::Text playerTextHP;
    Player* player;
public:
    sf::Clock gameTime;
    sf::Clock clickTimer;
    int score = 0;
    bool isGamePaused = true;
    bool isGameOver = false;
    Menu(sf::RenderWindow& windowRef, Player* playerRef);
    void update();
    void draw();
    void gameOver();
    void scoreUp(int howManyPoints);
};

//Przydatna funkcja
float distanceBetween(sf::Vector2f a, sf::Vector2f b);

