#include "InformationState.h"

InformationState::InformationState(std::stack<std::unique_ptr<State>>& states, sf::Vector2f& mousePosition, TextureHolder& textureHolder, sf::Font& font)
	: State(states, mousePosition, textureHolder, font)
{
	information.setFont(font);
	information.setPosition(sf::Vector2f(40, 20));
	information.setString(L"Gra zosta³a stworzona na XX Ogólnopolski Górowski Konkurs Informatyczny klas VII i VIII szkó³ podstawowych uczniów \nszkó³ ponadpodstawowych i klas ponadgimnazjalnych w roku szkolnym 2019 / 2020 przez Patryka Trojaka z kl.IIA \nz Liceum Ogólnokszta³c¹ce w Górze za pomoc¹ C++ oraz SFML https://www.sfml-dev.org/ \nZasady gry: Zadaniem graczem jest trafienia pociskiem w pojawiaj¹ce siê kwadraty. Za ka¿dego trafionego przeciwnika \nprzyznawany jest jeden punkt oraz jeden pocisk do amunicji. Co 5 zabitych przeciwnikow dodawany jest dodatkowy pocisk \ndo amunicji oraz zmniejszany jest zakres, z którego jest losowana wielkoœæ przeciwników. Gra koñczy siê, \ngdy graczowi skoñczy siê amunicja albo zdobêdzie 100 puntków.");
	information.setCharacterSize(35);
	information.setFillColor(sf::Color::White);
	information.setOutlineColor(sf::Color::Black);\

	control.setFont(font);
	control.setPosition(sf::Vector2f(40, 400));
	control.setString(L"Strza³: Lewy przycisk myszy\nZwiêkszenie si³y strza³u: W lub scroll w górê\nZmniejszenie si³y strza³u: S lub scroll w dó³\nObrót rakiety obliczany jest na podstawie pozycji myszy wzglêdem œrodka armaty.");
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
