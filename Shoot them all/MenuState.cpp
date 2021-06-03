#include "MenuState.h"


MenuState::MenuState(std::stack< std::unique_ptr< State > >& states, sf::Vector2f& mousePosition, TextureHolder& textureHolder, sf::Font& font)
	: State(states, mousePosition, textureHolder, font)
{
	wasMousePressed = false;
	background.setTexture(this->textureHolder.getTexture("Background"));
	background.setTextureRect(sf::IntRect(0, 0, 1500, 1000));
	initButtons();
}


MenuState::~MenuState()
{
}

void MenuState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
{
	wasMousePressed = false;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				wasMousePressed = true;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					makeMessageBoxAreYouSureToExit();
				}
			}
		}
	}
}

void MenuState::update(const float deltaTime)
{
	if (MessageBoxAreYouSureToExit)
		MessageBoxAreYouSureToExit->update(MousePosition);
	else
		updateButtons();
	updateInput(deltaTime);
}

void MenuState::updateInput(const float deltaTime)
{
	if (!MessageBoxAreYouSureToExit)
		handleFunctionalityOfButtons();
	handleFunctionalityOfMessageBox();
}

void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	drawButtons(target, states);
	if (MessageBoxAreYouSureToExit)
		target.draw(*MessageBoxAreYouSureToExit);
}

void MenuState::initButtons()
{
	buttons.insert(std::pair< std::string, Button >("GoToGameplayState", Button(sf::Vector2f(600, 500), sf::Vector2f(300, 70), textureHolder.getTexture("GreyButton300x70"), font, L"Graj", 50, textAlign::center)));
	buttons.insert(std::pair< std::string, Button >("GoToInformationState", Button(sf::Vector2f(600, 600), sf::Vector2f(300, 70), textureHolder.getTexture("GreyButton300x70"), font, L"Informacje", 50, textAlign::center)));
	buttons.insert(std::pair< std::string, Button >("ExitButton", Button(sf::Vector2f(600, 700), sf::Vector2f(300, 70), textureHolder.getTexture("GreyButton300x70"), font, L"WyjdŸ", 50, textAlign::center)));
}

void MenuState::handleFunctionalityOfButtons()
{
	if (buttons.at("GoToGameplayState").wasPressed(MousePosition, wasMousePressed))
	{
		wasMousePressed = false;
		states.push(std::make_unique<GameplayState>(states, MousePosition, textureHolder, font));
	}
	if (buttons.at("GoToInformationState").wasPressed(MousePosition, wasMousePressed))
	{
		wasMousePressed = false;
		states.push(std::make_unique<InformationState>(states, MousePosition, textureHolder, font));
	}
	if (buttons.at("ExitButton").wasPressed(MousePosition, wasMousePressed))
	{
		makeMessageBoxAreYouSureToExit();
	}	
}

void MenuState::handleFunctionalityOfMessageBox()
{
	if (MessageBoxAreYouSureToExit)
	{
		if (MessageBoxAreYouSureToExit->FirstOptionWasPressed(MousePosition, wasMousePressed))
			closeWindow = true; 
		else if (MessageBoxAreYouSureToExit->SecondOptionWasPressed(MousePosition, wasMousePressed))
			MessageBoxAreYouSureToExit.reset();
	}
}

void MenuState::updateButtons()
{
	for (auto& i : buttons)
	{
		i.second.update(MousePosition);
	}
}

void MenuState::drawButtons(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto const& i : buttons)
	{
		target.draw(i.second, states);
	}
}

void MenuState::makeMessageBoxAreYouSureToExit()
{
	MessageBoxAreYouSureToExit = std::make_unique<MessageBox>(view.getCenter(), sf::Vector2f(575, 200), sf::Vector2f(100, 55),
		textureHolder.getTexture("MessageboxBackground"), textureHolder.getTexture("GreyButton100x50"), font,
		L"Czy na pewno chcesz wyjœæ z gry?", L"Tak", L"Nie");
}



