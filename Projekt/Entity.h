#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Entity
{
protected:
    sf::RenderWindow& window;
    sf::Texture texture;

public:
    float hp;
    float maxHp;
    float movementSpeed;
    float attackPower;
    sf::Sprite body;
    void draw();
    virtual void update(float& dt) = 0;
    Entity(sf::RenderWindow& windowRefBase);
    bool alive = true;
};

