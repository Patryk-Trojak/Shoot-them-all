#include "Button.h"


Button::Button(const sf::Vector2f& Position, const sf::Vector2f& Size,
	const sf::Texture& Texture, const sf::Font& Font,
	const std::wstring Text, const unsigned CharacterSize, textAlign howAlignText, const float LeftMargin,
	const sf::Color IdleColor, const sf::Color HoverColor)
	:shape(Size), IdleColor(IdleColor), HoverColor(HoverColor),
	leftMargin(LeftMargin)
{
	state = ButtonState::idle;
	shape.setPosition(Position);
	shape.setTexture(&Texture);
	text.setString(Text);
	text.setCharacterSize(CharacterSize);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);
	text.setFont(Font);
	AlignText(howAlignText);
}

Button::~Button()
{
}

void Button::update(const sf::Vector2f& mousePosition)
{
	if (isMouseOverButton(mousePosition))
	{
		state = ButtonState::hover;
	}
	else
	{
		state = ButtonState::idle;
	}
	updateColorByButtonState();
}

bool Button::wasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed) const
{
	if (isMouseOverButton(mousePosition) && wasMouseLeftButtonPressed)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Button::setWstring(const std::wstring wstring, textAlign howAlignText)
{
	text.setString(wstring);
	AlignText(howAlignText);
}

void Button::setPosition(const sf::Vector2f& Position)
{
	shape.setPosition(Position);
}

sf::Vector2f Button::getPosition() const
{
	return shape.getPosition();
}

void Button::updateColorByButtonState()
{
	switch (state)
	{
	case ButtonState::idle:
		shape.setFillColor(IdleColor);
		break;
	case ButtonState::hover:
		shape.setFillColor(HoverColor);
		break;
	}
}

void Button::AlignText(textAlign howAlignText)
{
	switch (howAlignText)
	{
	case textAlign::center:
		text.setPosition(shape.getPosition().x + shape.getSize().x / 2 - text.getGlobalBounds().width / 2, shape.getPosition().y + shape.getSize().y / 2 - text.getGlobalBounds().height / 2 - text.getCharacterSize() / 5);
		break;
	case textAlign::left:
		text.setPosition(shape.getPosition().x + leftMargin, shape.getPosition().y + shape.getSize().y / 2 - text.getGlobalBounds().height / 2 - text.getCharacterSize() / 5);
		break;
	case textAlign::right:
		text.setPosition(shape.getPosition().x + shape.getSize().x - text.getGlobalBounds().width - 10, shape.getPosition().y + shape.getSize().y / 2 - text.getGlobalBounds().height / 2 - text.getCharacterSize() / 5);
		break;
	}
}

bool Button::isMouseOverButton(const sf::Vector2f& mousePosition) const
{
	if (shape.getGlobalBounds().contains(mousePosition))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(text, states);
}
