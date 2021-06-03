#pragma once
#include <SFML/Graphics.hpp>

class Enemy
	:public sf::Drawable
{
public:
	Enemy(const sf::Vector2f& Position, const sf::Vector2f& Size);
	~Enemy();
	sf::FloatRect getGlobalBounds() const;
private:
	sf::RectangleShape enemy;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

