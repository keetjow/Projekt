#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Projectile
{
private:
    sf::Texture texture;
    sf::RenderWindow& window;
    sf::Vector2f velocity;
    sf::Vector2f velocityN;

public:
    sf::Sprite body;
    float speed = 1300;
    float damage;
    Projectile(sf::RenderWindow& windowRef, sf::Vector2f startPos, sf::Vector2f velocity, float damageAmount);
    void update(float& dt);
    void draw();
};

