#include "PowerOfShotBar.h"

PowerOfShotBar::PowerOfShotBar(const sf::Texture& Texture, const float& powerOfShot, const sf::Font& Font)
{
	outlineOfBar.setSize(sf::Vector2f(300, 50));
	outlineOfBar.setPosition(sf::Vector2f(20, 1200));
	outlineOfBar.setOutlineThickness(4);
	outlineOfBar.setOutlineColor(sf::Color::Blue);
	outlineOfBar.setFillColor(sf::Color::Transparent);

	bar.setTexture(Texture);	
	bar.setTextureRect(sf::IntRect(0, 0, powerOfShot * 3, 100));
	bar.setPosition(sf::Vector2f(20, 1200));
	bar.setScale(1.f, 0.5f);

	power.setFont(Font);
	power.setCharacterSize(50);
	power.setPosition(sf::Vector2f(150, 1192));
	power.setOutlineThickness(1);
}

PowerOfShotBar::~PowerOfShotBar()
{
}

void PowerOfShotBar::update(const float& powerOfShot)
{
	power.setString( std::to_string( static_cast<int>(powerOfShot) ) );
	bar.setTextureRect(sf::IntRect(0, 0, powerOfShot * 3, 100));
}

void PowerOfShotBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(outlineOfBar);
	target.draw(bar);
	target.draw(power);
}
