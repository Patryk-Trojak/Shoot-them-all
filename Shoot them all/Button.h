#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class textAlign { center = 0, left, right };
enum class ButtonState { idle = 0, hover };

class Button
	:public sf::Drawable
{
public:
	Button(const sf::Vector2f& Position, const sf::Vector2f& Size,
		const sf::Texture& Texture, const sf::Font& Font,
		const std::wstring Text, const unsigned CharacterSize, textAlign howAlignText = textAlign::center, const float LeftMargin = 10,
		const sf::Color IdleColor = sf::Color::White, const sf::Color HoverColor = sf::Color::Red);
	virtual ~Button();
	void update(const sf::Vector2f& mousePosition);
	bool wasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed) const;
	void setWstring(const std::wstring wstring, textAlign howAlignText = textAlign::center);
	void setPosition(const sf::Vector2f& Position);
	sf::Vector2f getPosition() const;
	bool isMouseOverButton(const sf::Vector2f& mousePosition) const;

protected:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Color IdleColor;
	sf::Color HoverColor;
	ButtonState state;
	float leftMargin;
	void updateColorByButtonState();
	void AlignText(textAlign howAlignText);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

