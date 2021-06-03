#pragma once
#include<SFML/Graphics.hpp>
#include"State.h"

class InformationState
	:public State
{
public:
	InformationState(std::stack< std::unique_ptr< State > >& states, sf::Vector2f& mousePosition, TextureHolder& textureHolder, sf::Font& font);
	virtual ~InformationState();
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;
	virtual void update(const float deltaTime) override;
	virtual void updateInput(const float deltaTime) override;
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	sf::Text information;
	sf::Text control;
};