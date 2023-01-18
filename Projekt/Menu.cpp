#include <iostream>
#include "Menu.h"

//Menu constructor
Menu::Menu(sf::RenderWindow& windowRef, Player* playerRef) : window(windowRef), player(playerRef)
{
    this->font.loadFromFile("media/Minecraft.ttf");
    if (!this->font.loadFromFile("media/Minecraft.ttf"))
        std::cout << "Font error" << std::endl;

    //Heart setup
    this->heartTexture.loadFromFile("media/heart.png");
    this->heart.setTexture(this->heartTexture);
    this->heart.setOrigin(this->heart.getGlobalBounds().width / 2, this->heart.getGlobalBounds().height / 2);
    this->heart.scale(4, 4);

    //Text font setup
    this->scoreText.setFont(this->font);
    this->pause.setFont(this->font);
    this->dead.setFont(this->font);
    this->playerTextHP.setFont(this->font);
    this->statsTextEnemiesKilled.setFont(this->font);
    this->statsTextProjectilesShot.setFont(this->font);
    this->statsTextScore.setFont(this->font);
    this->statsTextTime.setFont(this->font);

    //Text content
    this->pause.setString("PRESS ENTER TO CONTINUE!");
    this->dead.setString("YOU ARE DEAD!");

    //Text origin
    this->pause.setOrigin(this->pause.getGlobalBounds().width / 2, this->pause.getGlobalBounds().height / 2);

    //Text position
    this->statsTextScore.setPosition((this->window.getSize().x / 2) + 300, (this->window.getSize().y / 2) - 40);
    this->statsTextEnemiesKilled.setPosition((this->window.getSize().x / 2) + 300, this->window.getSize().y / 2);
    this->statsTextProjectilesShot.setPosition((this->window.getSize().x / 2) + 300, (this->window.getSize().y / 2) + 40);
    this->statsTextTime.setPosition((this->window.getSize().x / 2) + 300, (this->window.getSize().y / 2) + 80);
    this->pause.setPosition(this->window.getSize().x / 2, (this->window.getSize().y / 2) - 100);
    this->dead.setPosition((this->window.getSize().x / 2) - 250, (this->window.getSize().y / 2) + 100);
    this->heart.setPosition(this->window.getSize().x - this->heart.getGlobalBounds().width / 2 - 20, this->heart.getGlobalBounds().height / 2 + 20);
    this->playerTextHP.setPosition(this->heart.getPosition().x - 150, this->heart.getPosition().y - 25);

    //Text color
    this->statsTextEnemiesKilled.setFillColor(sf::Color::White);
    this->statsTextProjectilesShot.setFillColor(sf::Color::White);
    this->playerTextHP.setFillColor(sf::Color::White);
    this->statsTextScore.setFillColor(sf::Color::White);
    this->statsTextTime.setFillColor(sf::Color::White);
    this->scoreText.setFillColor(sf::Color::White);
    this->pause.setFillColor(sf::Color::White);
    this->dead.setFillColor(sf::Color::Red);

    //Text size
    this->scoreText.setCharacterSize(35);
    this->playerTextHP.setCharacterSize(35);
    this->pause.setCharacterSize(35);
    this->dead.setCharacterSize(75);
    this->statsTextEnemiesKilled.setCharacterSize(20);
    this->statsTextProjectilesShot.setCharacterSize(20);
    this->statsTextScore.setCharacterSize(20);
    this->statsTextTime.setCharacterSize(20);
}

void Menu::update()
{
    this->playerTextHP.setString(std::to_string((int)this->player->hp) + "/" + std::to_string((int)this->player->maxHp));
    if (!this->isGameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->clickTimer.getElapsedTime().asSeconds() > 1)
    {
        if (this->isGamePaused)
        {
            this->isGamePaused = false;
            if (this->firstGame)
            {
                this->firstGame = false;
                this->gameTime.restart();
            }
        }

        else
            this->isGamePaused = true;

        this->clickTimer.restart();
    }

}

void Menu::gameOver()
{
    this->isGameOver = true;
    this->statsTextEnemiesKilled.setString("ENEMIES KILLED: " + std::to_string(this->player->enemiesKilled));
    this->statsTextProjectilesShot.setString("PROJECTILES SHOT: " + std::to_string(this->player->projectilesShot));
    this->statsTextScore.setString("FINAL SCORE: " + std::to_string(this->score));
    this->statsTextTime.setString("TIME: " + std::to_string((int)this->gameTime.getElapsedTime().asSeconds()));
}

void Menu::draw()
{
    this->window.draw(this->heart);
    this->window.draw(this->playerTextHP);
    this->window.draw(this->scoreText);
    if (this->isGamePaused)
        this->window.draw(this->pause);
    if (this->isGameOver)
    {
        this->window.draw(this->dead);
        this->window.draw(this->pause);
        this->window.draw(this->statsTextScore);
        this->window.draw(this->statsTextEnemiesKilled);
        this->window.draw(this->statsTextTime);
        this->window.draw(this->statsTextProjectilesShot);
    }
}

void Menu::scoreUp(int howManyPoints)
{
    this->score += howManyPoints;
    this->scoreText.setString("Score: " + std::to_string(this->score));
}

//Przydatne funkcje
float distanceBetween(sf::Vector2f a, sf::Vector2f b)
{
    sf::Vector2f vel = a - b;
    float distance = std::sqrt(std::pow(vel.x, 2) + std::pow(vel.y, 2));
    return distance;

}