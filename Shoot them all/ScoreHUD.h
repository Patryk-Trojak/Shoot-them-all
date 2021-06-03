#pragma once
#include <SFML/Graphics.hpp>

class ScoreHUD
	:public sf::Drawable
{
public:
	ScoreHUD(const sf::Font& Font, const int Score);
	~ScoreHUD();
	void update(const int Score);
private:
	sf::Text score;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

