#include "MessageBox.h"



MessageBox::MessageBox(const sf::Vector2f& PositionOfCenter, const sf::Vector2f& Size, const sf::Vector2f& sizeOfButtons,
	const sf::Texture& BackgroundTexture, const sf::Texture& ButtonsTexture, const sf::Font& Font,
	const std::wstring& TextOfMessageBox, const std::wstring& TextOfFirstOptionButton, const std::wstring& TextOfSecondOptionButton)
	: background(Size), PositionOfLEftUpperCorner(PositionOfCenter - Size / 2.f),
	FirstOption(sf::Vector2f(PositionOfLEftUpperCorner.x + 50, PositionOfLEftUpperCorner.y + Size.y - 70), sizeOfButtons, ButtonsTexture, Font, TextOfFirstOptionButton, 35),
	SecondOption(sf::Vector2f(PositionOfLEftUpperCorner.x + Size.x - 50 - sizeOfButtons.x, PositionOfLEftUpperCorner.y + Size.y - 70), sizeOfButtons, ButtonsTexture, Font, TextOfSecondOptionButton, 35)
{
	background.setPosition(PositionOfCenter - Size / 2.f);
	background.setTexture(&BackgroundTexture);
	text.setFont(Font);
	text.setString(TextOfMessageBox);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(background.getPosition().x + background.getSize().x / 2 - text.getGlobalBounds().width / 2, background.getPosition().y + 20);
}


MessageBox::~MessageBox()
{
}

bool MessageBox::FirstOptionWasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed)
{
	if (FirstOption.wasPressed(mousePosition, wasMouseLeftButtonPressed))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MessageBox::SecondOptionWasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed)
{
	if (SecondOption.wasPressed(mousePosition, wasMouseLeftButtonPressed))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MessageBox::update(sf::Vector2f& mousePosition)
{
	FirstOption.update(mousePosition);
	SecondOption.update(mousePosition);
}

void MessageBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(text, states);
	target.draw(FirstOption, states);
	target.draw(SecondOption, states);
}