#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "Projectile.h"
#include "Player.h"
#include "Enemies.h"
#include "Menu.h"

int main()
{
    //Window setup
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.f;
    sf::RenderWindow gameWindow(sf::VideoMode(1920, 1080, 32), "Projekt na zaliczenie", sf::Style::Fullscreen, settings);
    gameWindow.setFramerateLimit(60);
    gameWindow.setVerticalSyncEnabled(true);
    float dt;
    sf::Clock dt_clock;

    //Projectiles setup
    std::vector<Projectile*> projectiles;

    //Player setup
    sf::Vector2f mousePos;
    Player* player = new Player(gameWindow, mousePos, projectiles);

    //Menu setup
    Menu menu(gameWindow, player);
    sf::Clock deadScreenTimer;

    //Background setup
    sf::Texture backgroundTexture;
    sf::Sprite background;
    backgroundTexture.loadFromFile("media/background.png");
    background.setTexture(backgroundTexture);

    //Enemies setup
    std::vector<Enemy*> enemies;
    sf::Clock enemySpawnRate;
    srand(time(NULL));
    float spawnRate = 1;

    //Main loop
    while (gameWindow.isOpen())
    {
        dt = dt_clock.restart().asSeconds();
        //Event loop
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                gameWindow.close();
        }

        //Update mouse position
        mousePos = sf::Vector2f(sf::Mouse::getPosition(gameWindow));

        //Menu update
        menu.update();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menu.isGameOver && deadScreenTimer.getElapsedTime().asSeconds() > 1)
        {
            for (int i = 0; i < enemies.size(); i++)
            {
                delete enemies[i];
            }
            enemies.clear();
            for (int i = 0; i < projectiles.size(); i++)
            {
                delete projectiles[i];
            }
            projectiles.clear();
            player->body.setPosition(gameWindow.getSize().x / 2, gameWindow.getSize().y / 2);
            player->hp = player->maxHp;
            menu.score = 0;
            deadScreenTimer.restart();
            menu.clickTimer.restart();
            menu.gameTime.restart();
            menu.isGameOver = false;
        }

        //Game logic
        if (!menu.isGamePaused && !menu.isGameOver)
        {
            player->update(dt);
            //Spawning enemies
            if (enemySpawnRate.getElapsedTime().asSeconds() > spawnRate)
            {
                sf::Vector2f randomPosition;
                do
                {
                    randomPosition = sf::Vector2f(rand() % 1921, rand() % 1081);
                } while (distanceBetween(randomPosition, player->body.getPosition()) < 450);
                int randomNumber = rand() % 3;
                switch (randomNumber)
                {
                case 0:
                {
                    enemies.push_back(new BlueSlime(gameWindow, player, randomPosition));
                    break;
                }
                case 1:
                {
                    enemies.push_back(new GreenSlime(gameWindow, player, randomPosition));
                    break;
                }
                case 2:
                {
                    enemies.push_back(new OrangeSlime(gameWindow, player, randomPosition));
                    break;
                }
                }
                enemySpawnRate.restart();
            }

            for (int i = 0; i < projectiles.size(); i++)
            {
                projectiles[i]->update(dt);
                if (projectiles[i]->body.getPosition().x > 1920 || projectiles[i]->body.getPosition().x < 0 || projectiles[i]->body.getPosition().y > 1080 || projectiles[i]->body.getPosition().y < 0)
                {
                    delete projectiles[i];
                    projectiles.erase(projectiles.begin() + i);
                }
            }

            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i]->update(dt);
                for (int j = 0; j < projectiles.size(); j++)
                {
                    if (enemies[i]->body.getGlobalBounds().intersects(projectiles[j]->body.getGlobalBounds()))
                    {
                        enemies[i]->takeDamage(projectiles[j]->damage);
                        if (!enemies[i]->alive)
                        {
                            menu.scoreUp(enemies[i]->value);
                            player->enemiesKilled++;
                            delete enemies[i];
                            enemies.erase(enemies.begin() + i);
                        }
                        delete projectiles[j];
                        projectiles.erase(projectiles.begin() + j);
                        break;
                    }
                }
            }
            if (player->hp < 0)
            {
                player->hp = 0;
                menu.gameOver();
            }
        }
        //Drawing sprites
        gameWindow.clear();
        gameWindow.draw(background);
        player->draw();

        for (int i = 0; i < projectiles.size(); i++)
            projectiles[i]->draw();

        for (int i = 0; i < enemies.size(); i++)
            enemies[i]->draw();

        menu.draw();
        //Final frame display
        gameWindow.display();
    }
    return 0;
}