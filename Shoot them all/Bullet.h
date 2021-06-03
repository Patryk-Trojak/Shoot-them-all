#pragma once
#include <SFML/Graphics.hpp>


class Bullet
	: public sf::Drawable
{
public:
	Bullet(const sf::Vector2f& Position, const sf::Vector2f& Velocity);
	~Bullet();
	void move(const float deltaTime);
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const;
private:
	sf::CircleShape bullet;
	sf::Vector2f velocity;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

