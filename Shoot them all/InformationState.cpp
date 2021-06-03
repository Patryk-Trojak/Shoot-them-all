#include "InformationState.h"

InformationState::InformationState(std::stack<std::unique_ptr<State>>& states, sf::Vector2f& mousePosition, TextureHolder& textureHolder, sf::Font& font)
	: State(states, mousePosition, textureHolder, font)
{
	information.setFont(font);
	information.setPosition(sf::Vector2f(40, 20));
	information.setString(L"Gra zosta�a stworzona na XX Og�lnopolski G�rowski Konkurs Informatyczny klas VII i VIII szk� podstawowych uczni�w \nszk� ponadpodstawowych i klas ponadgimnazjalnych w roku szkolnym 2019 / 2020 przez Patryka Trojaka z kl.IIA \nz Liceum Og�lnokszta�c�ce w G�rze za pomoc� C++ oraz SFML https://www.sfml-dev.org/ \nZasady gry: Zadaniem graczem jest trafienia pociskiem w pojawiaj�ce si� kwadraty. Za ka�dego trafionego przeciwnika \nprzyznawany jest jeden punkt oraz jeden pocisk do amunicji. Co 5 zabitych przeciwnikow dodawany jest dodatkowy pocisk \ndo amunicji oraz zmniejszany jest zakres, z kt�rego jest losowana wielko�� przeciwnik�w. Gra ko�czy si�, \ngdy graczowi sko�czy si� amunicja albo zdob�dzie 100 puntk�w.");
	information.setCharacterSize(35);
	information.setFillColor(sf::Color::White);
	information.setOutlineColor(sf::Color::Black);\

	control.setFont(font);
	control.setPosition(sf::Vector2f(40, 400));
	control.setString(L"Strza�: Lewy przycisk myszy\nZwi�kszenie si�y strza�u: W lub scroll w g�r�\nZmniejszenie si�y strza�u: S lub scroll w d�\nObr�t rakiety obliczany jest na podstawie pozycji myszy wzgl�dem �rodka armaty.");
	control.setCharacterSize(35);
	control.setFillColor(sf::Color::White);

	background.setTexture(this->textureHolder.getTexture("Background"));
	background.setTextureRect(sf::IntRect(0, 0, 1500, 1000));
}

InformationState::~InformationState()
{
}

void InformationState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
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
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				states.pop();
			}
		}
	}
}


void InformationState::update(const float deltaTime)
{
}

void InformationState::updateInput(const float deltaTime)
{
}

void InformationState::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(background, state);
	target.draw(information, state);
	target.draw(control, state);
}
