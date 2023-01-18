#define _USE_MATH_DEFINES
#include "Player.h"

//Player constructor
Player::Player(sf::RenderWindow& windowRef, sf::Vector2f& mousePosRef, std::vector<Projectile*>& projectilesRef)
    :Entity(windowRef), mousePos(mousePosRef), projectiles(projectilesRef)
{
    //Body setup
    this->texture.loadFromFile("media/spr_character.png");
    this->body.setTexture(this->texture);
    this->body.setTextureRect(sf::IntRect(0, 0, 16, 16));
    this->body.setOrigin(this->body.getPosition().x + 8, this->body.getPosition().y + 8);
    this->body.setPosition(this->window.getSize().x / 2, this->window.getSize().y / 2);
    this->body.setScale(5, 5);
    //Stats setup
    this->movementSpeed = 550.f;
    this->maxHp = 25.f;
    this->hp = this->maxHp;
    this->attackPower = 10.f;
}

//Player methods
void Player::update(float& dt)
{
    //Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->body.move(0.f, -1.f * this->movementSpeed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->body.move(0.f, 1.f * this->movementSpeed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->body.move(-1.f * this->movementSpeed * dt, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->body.move(1.f * this->movementSpeed * dt, 0.f);

    //Looking at mouse direction
    float angle = std::atan2(this->mousePos.x - this->body.getPosition().x, this->mousePos.y - this->body.getPosition().y) * 180 / M_PI;
    this->body.setRotation(-angle);

    //Shooting
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->shoot();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        this->useAbility();
}

void Player::shoot()
{
    if (this->shootTimer.getElapsedTime().asMilliseconds() > this->fireRate)
    {
        sf::Vector2f velocity = this->mousePos - this->body.getPosition();
        this->projectiles.push_back(new Projectile(this->window, this->body.getPosition(), velocity, this->attackPower));
        this->shootTimer.restart();
        this->projectilesShot++;
    }
}

void Player::useAbility()
{
    if (this->abilityCooldown.getElapsedTime().asSeconds() > 4)
    {
        for (int i = 0; i < 16; i++)
        {
            float angle = i * M_PI / 8;
            sf::Vector2f velocity = sf::Vector2f(std::sin(angle), std::cos(angle) * (-1));
            this->projectiles.push_back(new Projectile(this->window, this->body.getPosition(), velocity, this->attackPower * 5.f));
        }
        this->projectilesShot += 16;
        abilityCooldown.restart();
    }
}