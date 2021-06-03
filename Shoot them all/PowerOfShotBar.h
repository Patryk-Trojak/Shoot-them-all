#pragma once
#include<SFML/Graphics.hpp>

class PowerOfShotBar
	: public sf::Drawable
{
public:
	PowerOfShotBar(const sf::Texture& Texture, const float& powerOfShot, const sf::Font& Font);
	~PowerOfShotBar();
	void update(const float& powerOfShot);

private:
	sf::Sprite bar;
	sf::RectangleShape outlineOfBar;
	sf::Text power;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

