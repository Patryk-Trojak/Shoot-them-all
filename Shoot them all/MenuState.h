#pragma once
#include <iostream>
#include <memory>
#include "State.h"
#include "GameplayState.h"
#include "Button.h"
#include "MessageBox.h"
#include "InformationState.h"

class MenuState :
	public State
{
public:
	MenuState(std::stack< std::unique_ptr< State > >& states, sf::Vector2f& mousePosition, TextureHolder& textureHolder, sf::Font& font);
	virtual ~MenuState();
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;
	virtual void update(const float deltaTime) override;
	virtual void updateInput(const float deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
protected:
	std::map < std::string, Button > buttons;
	std::unique_ptr<MessageBox> MessageBoxAreYouSureToExit;
	void updateButtons();
	void drawButtons(sf::RenderTarget& target, sf::RenderStates states) const;
	void makeMessageBoxAreYouSureToExit();
	void initButtons();
	void handleFunctionalityOfButtons();
	void handleFunctionalityOfMessageBox();

};

