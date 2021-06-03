#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& Position, const sf::Vector2f& Velocity)
	:velocity(Velocity)
{
	bullet.setPosition(Position);
	bullet.setRadius(20.f);
	bullet.setOrigin(bullet.getRadius() / 2.f, bullet.getRadius() / 2.f);
	bullet.setFillColor(sf::Color::Black);
}

Bullet::~Bullet()
{
}

void Bullet::move(const float deltaTime)
{
	bullet.move(velocity * deltaTime);
	velocity.y += 300 * deltaTime;
}

sf::FloatRect Bullet::getGlobalBounds() const
{
	return bullet.getGlobalBounds();
}

sf::Vector2f Bullet::getPosition() const
{
	return bullet.getPosition();
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bullet);
}


