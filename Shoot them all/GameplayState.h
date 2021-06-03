#pragma once
#include <memory>
#include <vector>
#include <random>
#include "State.h"
#include "Player.h"
#include "Game.h"
#include "PowerOfShotBar.h"
#include "Enemy.h"
#include "ScoreHUD.h"
#include "AmmoHUD.h"
#include "MessageBox.h"

/*
Faster way to remove elements in unsorded vector.
To the element that we want to erase we move last element from vector and we remove last element.
ONLY IF VECTOR DOESNT NEED TO BE SORTED
*/
template<class ValueType>
inline void fastErase(typename std::vector<ValueType>& container, typename std::vector<ValueType>::iterator it)
{
	auto lastEl = container.end() - 1;
	if (it != lastEl) {
		*it = std::move(*lastEl);
	}
	container.pop_back();
}

class GameplayState
	:public State
{
public:
	GameplayState(std::stack< std::unique_ptr< State > >& states, sf::Vector2f& mousePosition, TextureHolder& textureHolder, sf::Font& font);
	virtual ~GameplayState();
	virtual void update(const float deltaTime) override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;

private:
	virtual void updateInput(const float deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void restartGame();

	//MessageBox
	std::unique_ptr<MessageBox> MessageBoxAboutEndOfGame;
	void makeMessageBoxEndOfGame(const std::wstring& textOfMessageBox);
	void handleFuncionalityOfMessagBoxEndOFGame();

	Player player;
	int score;

	//HUD
	PowerOfShotBar powerOfShotBar;
	ScoreHUD scoreHUD;
	AmmoHUD ammo;

	//Bullets
	std::vector<Bullet> bullets;
	void drawBullets(sf::RenderTarget& target, sf::RenderStates states) const;
	void moveBullets(const float deltaTime);
	void eraseBulletsIfTheyOutOfWindow();

	//Enemy
	std::unique_ptr<Enemy> enemy;
	void createEnemy();

	//Randomize Position Of Enemy
	std::random_device dev;
	std::mt19937 rng;
	int minPositionXOfEnemy;
	int minPositionYOfEnemy;
	int maxPositionXOfEnemy;
	int maxPositionYOfEnemy;
	int currentMinSizeOfEnemy;
	int currentMaxSizeOfEnemy;
	sf::Vector2f drawPositionOfEnemy();
	sf::Vector2f drawSizeOfEnemy();
	void setDistributionOfSizeOfEnemyDependingOnScore();

	//collisions
	void collisionProjectilesAndEnemy();
};

