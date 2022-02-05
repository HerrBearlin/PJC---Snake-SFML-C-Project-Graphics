#pragma once
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "GameState.h" //it's a state
#include "SnakeGame.h"


class MainMenu : public Tools::GameState
{
private:
	std::shared_ptr<SnakeGameHolder> my_SnakeGameHolder;
	sf::Text my_GameTitle;

	sf::Text my_PlayButton;
	sf::Text my_ExitButton;

	bool my_PlayButtonIsSelected;
	bool my_PlayButtonIsPressed;
	bool my_ExitButtonIsSelected;
	bool my_ExitButtonIsPressed;



public:
	//we do not want to create an object of MainMenu State without providing snakeGameHolder
	MainMenu(std::shared_ptr<SnakeGameHolder> &SnakeGameHolder);
	~MainMenu();

	void Initialising() override;
	void InputReader() override;
	void UpdateGameState(sf::Time deltaTime) override; //Assuming constant FrameRate like in Unity, so FPS is the same;
	void Draw() override; //Drawing Graphics
};

