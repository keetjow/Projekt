#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
    sf::Clock punchTimer;
    Entity* target;
    bool knockbackState = false;
    sf::Clock knockbackTimer;
    sf::Vector2f velocity;
    sf::Vector2f moveVector;
    bool flipChange = false;

public:
    int value;
    void update(float& dt);
    Enemy(sf::RenderWindow& windowRef, Entity* targetRef);
    void takeDamage(float damageReceiveAmount);
};

class BlueSlime : public Enemy
{
public:
    BlueSlime(sf::RenderWindow& windowRef, Entity* targetRef, sf::Vector2f startPos);
};

class GreenSlime : public Enemy
{
public:
    GreenSlime(sf::RenderWindow& windowRef, Entity* targetRef, sf::Vector2f startPos);
};

class OrangeSlime : public Enemy
{
public:
    OrangeSlime(sf::RenderWindow& windowRef, Entity* targetRef, sf::Vector2f startPos);
};
