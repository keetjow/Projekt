#include "Entity.h"

//Entity drawing setup
Entity::Entity(sf::RenderWindow& windowRefBase) : window(windowRefBase) {};
void Entity::draw()
{
    this->window.draw(this->body);
}