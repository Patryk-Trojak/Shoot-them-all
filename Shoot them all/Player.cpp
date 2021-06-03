#include "Player.h"

Player::Player(const sf::Texture& TextureOfCannon, const sf::Texture& TextureOfBase)
    :powerOfShoot(50.f),
    ammo{5}
{
    base.setPosition(sf::Vector2f(30, 1100));
    base.setTexture(TextureOfBase);
    cannon.setPosition(sf::Vector2f(130, 1130));
    cannon.setTexture(TextureOfCannon);
    cannon.setOrigin(sf::Vector2f(30, 28));
}


Player::~Player()
{
}

void Player::updateRotation(const sf::Vector2f& MousePosition)
{
    if (MousePosition.x >= cannon.getPosition().x and MousePosition.y <= cannon.getPosition().y)
    {
        float a = (cannon.getPosition().y - MousePosition.y);
        float c = sqrt(pow(cannon.getPosition().x - MousePosition.x, 2) + pow(a, 2));
        cannon.setRotation(-asin(a / c) * 180 / 3.14);
    }
    else if (MousePosition.x < cannon.getPosition().x)
        cannon.setRotation(-90);
    else
        cannon.setRotation(0);

}

void Player::updatePowerOfShoot(const float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        powerOfShoot += 50 * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        powerOfShoot -= 50 * deltaTime;
    }
    if (powerOfShoot < 1)
    {
        powerOfShoot = 1;
    }
    if (powerOfShoot > 100)
    {
        powerOfShoot = 100;
    }
}

void Player::shoot(std::vector<Bullet>& bullets, const bool wasMousePressed)
{
    if (wasMousePressed and ammo > 0)
    {
        sf::Vector2f velocityOfProjectile = sf::Vector2f(powerOfShoot * 10 * cos(cannon.getRotation() * M_PI / 180), powerOfShoot * 10 * sin(cannon.getRotation() * M_PI / 180));
        sf::Vector2f InitialPositionOfProjectile = sf::Vector2f((cannon.getPosition().x) + cos(cannon.getRotation() * M_PI / 180) * 90 + sin(cannon.getRotation() * M_PI / 180) * 5, (cannon.getPosition().y) + sin(cannon.getRotation() * M_PI / 180) * 90 - cos(cannon.getRotation() * M_PI / 180) * 5);
        bullets.emplace_back(InitialPositionOfProjectile, velocityOfProjectile);
        ammo--;
    }
}

void Player::addPowerOfShoot(const float x)
{
    powerOfShoot += x;
    if (powerOfShoot < 1)
    {
        powerOfShoot = 1;
    }
    if (powerOfShoot > 100)
    {
        powerOfShoot = 100;
    }
}

float Player::getPowerOfShoot() const
{
    return powerOfShoot;
}

void Player::setPowerOfShoot(const float NewPowerOfShot)
{
    powerOfShoot = NewPowerOfShot;
}

int Player::getAmmo() const
{
    return ammo;
}

void Player::addAmmo(const int value)
{
    ammo += value;
}

void Player::setAmmo(const int NewNumberOfAmmo)
{
    ammo = NewNumberOfAmmo;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(cannon, states);
    target.draw(base, states);
}


