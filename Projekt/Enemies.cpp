#include "Enemies.h"

//Enemies constructors
Enemy::Enemy(sf::RenderWindow& windowRef, Entity* targetRef)
    :Entity(windowRef), target(targetRef) {}


BlueSlime::BlueSlime(sf::RenderWindow& windowRef, Entity* targetRef, sf::Vector2f startPos) : Enemy(windowRef, targetRef)
{
    //Body setup
    this->value = 1;
    this->texture.loadFromFile("media/slime_blue_normal.png");
    this->body.setTexture(this->texture);
    this->body.setTextureRect(sf::IntRect(0, 0, 16, 16));
    this->body.setOrigin(this->body.getPosition().x + 8, this->body.getPosition().y + 8);
    this->body.setScale(5, 5);
    this->body.setPosition(startPos);
    //Stats setup
    this->movementSpeed = 250.f;
    this->maxHp = 10.f;
    this->hp = this->maxHp;
    this->attackPower = 5.f;
}

GreenSlime::GreenSlime(sf::RenderWindow& windowRef, Entity* targetRef, sf::Vector2f startPos) : Enemy(windowRef, targetRef)
{
    //Body setup
    this->value = 2;
    this->texture.loadFromFile("media/slime_green_normal.png");
    this->body.setTexture(this->texture);
    this->body.setTextureRect(sf::IntRect(0, 0, 16, 16));
    this->body.setOrigin(this->body.getPosition().x + 8, this->body.getPosition().y + 8);
    this->body.setScale(7, 7);
    this->body.setPosition(startPos);
    //Stats setup
    this->movementSpeed = 220.f;
    this->maxHp = 20.f;
    this->hp = this->maxHp;
    this->attackPower = 7.f;
}

OrangeSlime::OrangeSlime(sf::RenderWindow& windowRef, Entity* targetRef, sf::Vector2f startPos) : Enemy(windowRef, targetRef)
{
    //Body setup
    this->value = 3;
    this->texture.loadFromFile("media/slime_orange_normal.png");
    this->body.setTexture(this->texture);
    this->body.setTextureRect(sf::IntRect(0, 0, 16, 16));
    this->body.setOrigin(this->body.getPosition().x + 8, this->body.getPosition().y + 8);
    this->body.setScale(9, 9);
    this->body.setPosition(startPos);
    //Stats setup
    this->movementSpeed = 190.f;
    this->maxHp = 50.f;
    this->hp = this->maxHp;
    this->attackPower = 10.f;
}

//Enemy update
void Enemy::update(float& dt)
{
    this->velocity = this->target->body.getPosition() - this->body.getPosition();
    float dist = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));
    sf::Vector2f velocityN = this->velocity / dist;
    if (dist > 10 && !this->knockbackState)
        this->moveVector = velocityN * this->movementSpeed;

    if (this->body.getGlobalBounds().intersects(this->target->body.getGlobalBounds()) && this->punchTimer.getElapsedTime().asSeconds() > 1)
    {
        this->knockbackTimer.restart();
        this->punchTimer.restart();
        this->target->hp -= this->attackPower;
        this->knockbackState = true;
        this->moveVector = velocityN * (-1.f) * this->movementSpeed;
    }
    if (knockbackTimer.getElapsedTime().asMilliseconds() > 500)
        this->knockbackState = false;

    if (this->moveVector.x > 0)
    {
        if (this->flipChange)
        {
            this->body.scale(-1, 1);
            this->flipChange = false;
        }
    }
    else
    {
        if (!this->flipChange)
        {
            this->body.scale(-1, 1);
            this->flipChange = true;
        }
    }
    this->body.move(this->moveVector * dt);
}

//Enemy damage managment
void Enemy::takeDamage(float damageReceiveAmount)
{
    if ((this->body.getScale().x > 2.5f || this->body.getScale().x < -2.5f) && this->body.getScale().y > 2.5f)
        this->body.setScale(this->body.getScale().x - this->body.getScale().x / 10, this->body.getScale().y - this->body.getScale().y / 10);

    this->hp -= damageReceiveAmount;
    this->movementSpeed -= 10;
    if (this->hp <= 0)
        this->alive = false;
}