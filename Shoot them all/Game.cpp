#include "Game.h"

Game::Game()
	:window(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 1.32, sf::VideoMode::getDesktopMode().height / 1.09), "Gra na konkurs informatyczny")
{
	loadAllTextures();
	font.loadFromFile("orange kid.ttf");
	currentState.emplace(std::make_unique< MenuState >(currentState, MousePosition, textureHolder, font));
	window.setPosition(sf::Vector2i(0, 5));
}


Game::~Game()
{
}

void Game::run()
{
	while (window.isOpen())
	{
		if (currentState.top()->getCloseWindow())
			window.close();
		updateSFMLEvents();
		updateDeltaTime();
		updateMousePosition();
		update();
		setView();
		render();
	}
}

void Game::render()
{
	window.clear();
	window.draw(*currentState.top());
	window.display();
}

void Game::update()
{
	currentState.top()->update(deltaTime);
}

void Game::updateSFMLEvents()
{
	currentState.top()->handleSFMLEvent(window, event);
}

void Game::updateDeltaTime()
{
	deltaTime = deltaTimeClock.restart().asSeconds();
}

void Game::updateMousePosition()
{
	MousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void Game::loadAllTextures()
{
	
	textureHolder.loadTexture("GreyButton300x70", ".\\Textures\\GreyButton300x70.png");
	textureHolder.loadTexture("Background", ".\\Textures\\Background.png");
	textureHolder.loadTexture("Cannon", ".\\Textures\\Cannon.png");
	textureHolder.loadTexture("PowerOfShotBar", ".\\Textures\\PowerOfShotBar.png");
	textureHolder.loadTexture("BaseForCannon", ".\\Textures\\BaseForCannon.png");
	textureHolder.loadTexture("GreyButton100x50", ".\\Textures\\GreyButton100x50.png");
	textureHolder.loadTexture("MessageboxBackground", ".\\Textures\\MessageboxBackground.png");
}

void Game::setView()
{
	currentState.top()->setView(window);
}



