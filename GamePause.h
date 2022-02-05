#pragma once
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "GameState.h" //it's a state
#include "SnakeGame.h"


class GamePause : public Tools::GameState
{
private:
	std::shared_ptr<SnakeGameHolder> my_SnakeGameHolder;
	sf::Text my_GamePauseTitle;

	


public:
	//we do not want to create an object of MainMenu State without providing snakeGameHolder
	GamePause(std::shared_ptr<SnakeGameHolder>& SnakeGameHolder);
	~GamePause();

	void Initialising() override;
	void InputReader() override;
	void UpdateGameState(sf::Time deltaTime) override; //Assuming constant FrameRate like in Unity, so FPS is the same;
	void Draw() override; //Drawing Graphics
};
