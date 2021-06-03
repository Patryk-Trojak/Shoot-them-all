#include "State.h"


State::State(std::stack< std::unique_ptr< State > >& states, sf::Vector2f& mousePosition, TextureHolder& textureHolder, sf::Font& font)
	:states(states), MousePosition(mousePosition), textureHolder(textureHolder), font(font)
{
	view.setSize(1500, 1000);
	view.setCenter(750, 500);
	closeWindow = false;
	wasMousePressed = false;
}


State::~State()
{
}

void State::setView(sf::RenderWindow& window)
{
	window.setView(view);
}

bool State::getCloseWindow()
{
	return closeWindow;
}

