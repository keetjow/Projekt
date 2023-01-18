#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include "Entity.h"
#include "Projectile.h"

class Player : public Entity
{
private:
    void shoot();
    void useAbility();
    float fireRate = 200;
    sf::Vector2f& mousePos;
    std::vector<Projectile*>& projectiles;
    sf::Clock shootTimer;
    sf::Clock abilityCooldown;

public:
    int enemiesKilled = 0;
    int projectilesShot = 0;
    Player(sf::RenderWindow& windowRef, sf::Vector2f& mousePosRef, std::vector<Projectile*>& projectilesRef);
    void update(float& dt);
};