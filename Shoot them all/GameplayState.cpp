#include "GameplayState.h"

GameplayState::GameplayState(std::stack<std::unique_ptr<State>>& states, sf::Vector2f& mousePosition, TextureHolder& textureHolder, sf::Font& font)
	:State(states, mousePosition, textureHolder, font),
	score{ 1 },
	player(textureHolder.getTexture("Cannon"), textureHolder.getTexture("BaseForCannon")),
	powerOfShotBar(textureHolder.getTexture("PowerOfShotBar"), player.getPowerOfShoot(), font),
	rng(dev()),
	minPositionXOfEnemy{450}, minPositionYOfEnemy{ 10 },
	maxPositionXOfEnemy{ 1800 }, maxPositionYOfEnemy{ 1100 },
	currentMinSizeOfEnemy{ 200 }, currentMaxSizeOfEnemy{ 400 },
	scoreHUD(font, score),
	ammo(font, player.getAmmo())
{
	view.setSize(sf::Vector2f(2000, 1333));
	view.setCenter(sf::Vector2f(1000, 666));
	background.setTexture(this->textureHolder.getTexture("Background"));
	background.setTextureRect(sf::IntRect(0, 0, 2000, 1333));
	createEnemy();
}

GameplayState::~GameplayState()
{

}

void GameplayState::update(const float deltaTime)
{
	if (!MessageBoxAboutEndOfGame)
	{	
		//Player
		player.updateRotation(MousePosition);
		player.updatePowerOfShoot(deltaTime);
		player.shoot(bullets, wasMousePressed);
		//Bullets
		moveBullets(deltaTime);
		eraseBulletsIfTheyOutOfWindow();
		//HUD
		powerOfShotBar.update(player.getPowerOfShoot());
		ammo.update(player.getAmmo());
		scoreHUD.update(score);
		//Colisions
		collisionProjectilesAndEnemy();
		if (player.getAmmo() <= 0 and bullets.empty())
		{
			makeMessageBoxEndOfGame(L"Niestety, skoñczy³a ci siê amunicja\nUzyska³eœ " + std::to_wstring(score) + L" punktów");
		}
	}
	else
	{
		MessageBoxAboutEndOfGame->update(MousePosition);
		handleFuncionalityOfMessagBoxEndOFGame();
	}

}

void GameplayState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
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
				makeMessageBoxEndOfGame(L"Co chcesz zrobiæ?\nWciœnij LPM, ¿eby kontynuowaæ rozgrywkê.");
			}
		}

		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta > 0)
			{
				player.addPowerOfShoot(1.f);
			}
			else if (event.mouseWheelScroll.delta < 0)
			{
				player.addPowerOfShoot(-1.f);
			}
		}
	}
}

void GameplayState::updateInput(const float deltaTime)
{

}

void GameplayState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background);
	target.draw(player);
	drawBullets(target, states);
	if (enemy)
	{
		target.draw(*enemy);
	}
	target.draw(powerOfShotBar);
	target.draw(scoreHUD);
	target.draw(ammo);
	if (MessageBoxAboutEndOfGame)
	{
		target.draw(*MessageBoxAboutEndOfGame, states);
	}
}

void GameplayState::makeMessageBoxEndOfGame(const std::wstring& textOfMessageBox)
{
	MessageBoxAboutEndOfGame = std::make_unique<MessageBox>(view.getCenter(), sf::Vector2f(700, 200), sf::Vector2f(200, 50),
		textureHolder.getTexture("MessageboxBackground"), textureHolder.getTexture("GreyButton100x50"), font,
		textOfMessageBox, L"Powrót do menu", L"Zacznij od nowa");
}

void GameplayState::handleFuncionalityOfMessagBoxEndOFGame()
{
	if (MessageBoxAboutEndOfGame)
	{
		if (MessageBoxAboutEndOfGame->FirstOptionWasPressed(MousePosition, wasMousePressed))
		{
			states.pop();
		}
		else if (MessageBoxAboutEndOfGame->SecondOptionWasPressed(MousePosition, wasMousePressed))
		{
			restartGame();
			MessageBoxAboutEndOfGame.reset();
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			MessageBoxAboutEndOfGame.reset();
		}
	}
}

void GameplayState::restartGame()
{
	player.setAmmo(5);
	player.setPowerOfShoot(50.f);
	score = 1;
	currentMinSizeOfEnemy = 200;
	currentMaxSizeOfEnemy = 400;
	bullets.clear();
	createEnemy();
}

void GameplayState::drawBullets(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto const &i : bullets)
	{
		target.draw(i);
	}
}

void GameplayState::moveBullets(const float deltaTime)
{
	for (auto& i : bullets)
	{
		i.move(deltaTime);
	}
}

void GameplayState::eraseBulletsIfTheyOutOfWindow()
{
	auto bullet = bullets.begin();
	while (!bullets.empty())
	{
		bool isLastElement = false;
		if (bullet == bullets.end() - 1)
			isLastElement = true;

		if (bullet->getPosition().x > 2100 or bullet->getPosition().y > 1400)
		{
			fastErase(bullets, bullet);
		}
		else
		{
			bullet++;
		}

		if (isLastElement)
			break;
	}
}

void GameplayState::createEnemy()
{
	enemy = std::make_unique<Enemy>(drawPositionOfEnemy(), drawSizeOfEnemy());
}

sf::Vector2f GameplayState::drawPositionOfEnemy()
{
	return sf::Vector2f( std::uniform_int_distribution<int>{ minPositionXOfEnemy, maxPositionXOfEnemy }(rng), std::uniform_int_distribution<int>{ minPositionYOfEnemy, maxPositionYOfEnemy }(rng) );
}

sf::Vector2f GameplayState::drawSizeOfEnemy()
{
	float size = std::uniform_int_distribution<int>{ currentMinSizeOfEnemy, currentMaxSizeOfEnemy }(rng);
	return sf::Vector2f(size, size);
}

void GameplayState::setDistributionOfSizeOfEnemyDependingOnScore()
{
	if (score % 5 == 0)
	{
		if (currentMinSizeOfEnemy > 10)
		{
			currentMinSizeOfEnemy /= 1.2;
			currentMaxSizeOfEnemy /= 1.2;
		}
	}
}

void GameplayState::collisionProjectilesAndEnemy()
{
	auto bullet = bullets.begin();

	while (!bullets.empty())
	{
		bool isLastElement = false;
		if (bullet == bullets.end() - 1)
			isLastElement = true;

		if (bullet->getGlobalBounds().intersects(enemy->getGlobalBounds()))
		{
			fastErase(bullets, bullet);
			createEnemy();
			score++;
			player.addAmmo();
			if (score % 5 == 0)
			{
				player.addAmmo();
			}
			setDistributionOfSizeOfEnemyDependingOnScore();
			if (score == 100)
			{
				makeMessageBoxEndOfGame(L"Gratulacje! Zdoby³eœ maksymaln¹ liczbê punktów!");
			}
		}
		else
		{
			bullet++;
		}

		if (isLastElement)
			break;
	}
}
