#include "Projectile.h"

//Projectile constructor
Projectile::Projectile(sf::RenderWindow& windowRef, sf::Vector2f startPos, sf::Vector2f velocity, float damageAmount)
    :window(windowRef), damage(damageAmount)
{
    this->texture.loadFromFile("media/projectiles.png");
    this->body.setTexture(this->texture);
    this->body.setTextureRect(sf::IntRect(16, 8, 8, 8));
    this->body.setOrigin(this->body.getPosition().x + 4, this->body.getPosition().y + 4);
    this->body.setPosition(startPos);
    this->body.setScale(2, 2);
    this->velocity = velocity;
    float dist = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));
    this->velocityN = velocity / dist;
}

//Projectile methods
void Projectile::update(float& dt)
{
    this->body.move(this->velocityN * this->speed * dt);
}

void Projectile::draw()
{
    this->window.draw(this->body);
}