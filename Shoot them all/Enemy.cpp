#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& Position, const sf::Vector2f& Size)
{
	enemy.setSize(Size);
	enemy.setPosition(Position);
	enemy.setFillColor(sf::Color::Red);
}

Enemy::~Enemy()
{
}

sf::FloatRect Enemy::getGlobalBounds() const
{
	return enemy.getGlobalBounds();
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(enemy);
}
