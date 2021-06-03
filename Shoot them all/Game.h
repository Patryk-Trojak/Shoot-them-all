#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include "State.h"
#include "TextureHolder.h"
#include "MenuState.h"

class Game
{
public:
	Game();
	virtual ~Game();
	void run();

private:
	sf::RenderWindow window;
	std::stack < std::unique_ptr< State > > currentState;
	TextureHolder textureHolder;
	sf::Font font;
	sf::Clock deltaTimeClock;
	sf::Event event;
	sf::Vector2f MousePosition;
	std::map<std::string, sf::Keyboard::Key> keybinds;
	float deltaTime;
	bool closeWindow;
	void render();
	void update();
	void updateSFMLEvents();
	void updateDeltaTime();
	void updateMousePosition();
	void loadAllTextures();
	void setView();
};

