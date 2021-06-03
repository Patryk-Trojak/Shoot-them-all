#pragma once
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include "Bullet.h"

class Player
    : public sf::Drawable
{
public:
    Player(const sf::Texture& TextureOfCannon, const sf::Texture& TextureOfBase);
    virtual ~Player();
    void updateRotation(const sf::Vector2f& MousePosition);
    void updatePowerOfShoot(const float deltaTime);
    void shoot(std::vector<Bullet>& bullets, const bool wasMousePressed);
    void addPowerOfShoot(const float x);
    float getPowerOfShoot() const;
    void setPowerOfShoot(const float NewPowerOfShot);
    int getAmmo() const;
    void addAmmo(const int value = 1);
    void setAmmo(const int NewNumberOfAmmo);
private:
    sf::Sprite base;
    sf::Sprite cannon;
    float powerOfShoot;
    int ammo;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};