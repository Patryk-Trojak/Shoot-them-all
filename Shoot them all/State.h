#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>
#include <array>
#include "TextureHolder.h"



class State
	:public sf::Drawable
{
public:
	State(std::stack< std::unique_ptr< State > >& states, sf::Vector2f& mousePosition, TextureHolder& textureHolder, sf::Font& font);
	virtual ~State();
	virtual void update(const float deltaTime) = 0;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) = 0;
	void setView(sf::RenderWindow& window);
	bool getCloseWindow();
protected:
	std::stack< std::unique_ptr< State > >& states;
	TextureHolder& textureHolder;
	sf::Font& font;
	sf::Vector2f& MousePosition;
	sf::Sprite background;
	sf::View view;
	bool closeWindow;
	virtual void updateInput(const float deltaTime) = 0;
	bool wasMousePressed;
};

