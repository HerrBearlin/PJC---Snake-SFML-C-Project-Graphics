#pragma once


#include <memory>
#include <iostream>
#include <array>


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Text.hpp>

#include "SnakeGame.h"
#include "GameState.h"
#include "Snekko.h"


class GameView : public Tools::GameState
{
private:
	std::shared_ptr<SnakeGameHolder> my_SnakeGameHolder;
	sf::Sprite my_Background;
	sf::Sprite my_Point;

	std::array<sf::Sprite, 4> my_Borders;

	Snekko my_Snake;
	sf::Vector2f my_SnakeDirection;
	sf::Time my_ElapsedTime;

	sf::Text my_ScoreText;
	int my_Score = 0;

public:
	GameView(std::shared_ptr<SnakeGameHolder>& SnakeGameHolder);
	~GameView();

	//VIRTUAL GIVES POLYMORPHISM OVERRIDING FUNCTIONS! :)))
	void Initialising()override;
	void InputReader() override;
	void UpdateGameState(sf::Time deltaTime) override;
	void Draw() override;

	void Pause() override;
	void Start() override;



};

