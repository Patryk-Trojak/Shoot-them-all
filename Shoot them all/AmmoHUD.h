#pragma once
#include <SFML/Graphics.hpp>


class AmmoHUD
	:public sf::Drawable
{
public:
	AmmoHUD(const sf::Font& Font, const int NumberOfAmmo);
	~AmmoHUD();
	void update(const int NumberOfAmmo);

private:
	sf::Text ammo;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};