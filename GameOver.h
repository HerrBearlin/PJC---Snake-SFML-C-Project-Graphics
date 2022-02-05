#pragma once
#pragma once
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "GameState.h" //it's a state
#include "SnakeGame.h"


class GameOver : public Tools::GameState
{
private:
	std::shared_ptr<SnakeGameHolder> my_SnakeGameHolder;
	sf::Text my_GameOverTitle;

	sf::Text my_RetryButton;
	sf::Text my_ExitButton;

	bool my_RetryButtonIsSelected;
	bool my_RetryButtonIsPressed;
	bool my_ExitButtonIsSelected;
	bool my_ExitButtonIsPressed;



public:
	//we do not want to create an object of MainMenu State without providing snakeGameHolder
	GameOver(std::shared_ptr<SnakeGameHolder>& SnakeGameHolder);
	~GameOver();

	void Initialising() override;
	void InputReader() override;
	void UpdateGameState(sf::Time deltaTime) override; //Assuming constant FrameRate like in Unity, so FPS is the same;
	void Draw() override; //Drawing Graphics
};


