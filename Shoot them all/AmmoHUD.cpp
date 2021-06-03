#include "AmmoHUD.h"

AmmoHUD::AmmoHUD(const sf::Font& Font, const int NumberOfAmmo)
{
	ammo.setFont(Font);
	ammo.setPosition(sf::Vector2f(20, 1250));
	ammo.setOutlineColor(sf::Color::Black);
	ammo.setFillColor(sf::Color::White);
	ammo.setString("Amunicja: " + std::to_string(NumberOfAmmo));
	ammo.setCharacterSize(50);
}

AmmoHUD::~AmmoHUD()
{
}

void AmmoHUD::update(const int NumberOfAmmo)
{
	ammo.setString("Amunicja: " + std::to_string(NumberOfAmmo));
}

void AmmoHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(ammo, states);
}