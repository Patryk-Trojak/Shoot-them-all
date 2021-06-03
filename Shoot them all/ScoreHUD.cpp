#include "ScoreHUD.h"

ScoreHUD::ScoreHUD(const sf::Font& Font, const int Score)
{
	score.setFont(Font);
	score.setPosition(sf::Vector2f(330, 1190));
	score.setOutlineColor(sf::Color::Black);
	score.setFillColor(sf::Color::White);
	score.setString("Wynik: " + std::to_string(Score));
	score.setCharacterSize(50);
}

ScoreHUD::~ScoreHUD()
{
}

void ScoreHUD::update(const int Score)
{
	score.setString("Wynik: " + std::to_string(Score));
}


void ScoreHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(score, states);
}
