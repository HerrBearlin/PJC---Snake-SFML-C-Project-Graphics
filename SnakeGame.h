#pragma once
#include <memory>


#include "GameAssetsCommands.h"
#include "GameState.h"
#include "GameStateManager.h"

#include <SFML/Graphics/RenderWindow.hpp>
enum DownloadID
{
	MENU_FONT = 0,
	GRASS_BACKGROUND_SPRITE,
	BORDER_SPRITE,
	POINT_SPRITE,
	SNAKE_SPRITE
};



struct SnakeGameHolder
{
	std::unique_ptr<Tools::GameAssetsCommands> my_gameAssets;
	std::unique_ptr<Tools::GameStateManager> my_gameStates;
	std::unique_ptr<sf::RenderWindow> my_gameWindow;

	SnakeGameHolder()
	{
		my_gameAssets = std::make_unique < Tools::GameAssetsCommands>();
		my_gameStates = std::make_unique < Tools::GameStateManager>();
		my_gameWindow = std::make_unique < sf::RenderWindow>();
	}
};



class SnakeGame
{
private:
	//shared holder for all the states
	std::shared_ptr<SnakeGameHolder> my_SnakeGameHolder;
	const sf::Time framePerSecond = sf::seconds(1.f / 60.f); // 60fps

public:
	SnakeGame();
	~SnakeGame();

	void RunGame();
};

