#include "GamePause.h"
#include <iostream>

#include <SFML/Window/Event.hpp>

GamePause::GamePause(std::shared_ptr<SnakeGameHolder> &SnakeGameHolder) : my_SnakeGameHolder(SnakeGameHolder)

{

}
GamePause::~GamePause()
{

}

void GamePause::Initialising()
{
	//TITLE
	//my_SnakeGameHolder->my_gameAssets->LoadFont(MENU_FONT, "assets/downloads/fonts/Calligraffitti-Regular.ttf");
	my_GamePauseTitle.setFont(my_SnakeGameHolder->my_gameAssets->GetFont(MENU_FONT));
	const sf::Font& font = my_SnakeGameHolder->my_gameAssets->GetFont(MENU_FONT);

	std::cout << "Font memory after get = " << &font << "\n";
	std::cout << "Font Successfully loaded" << std::endl;

	my_GamePauseTitle.setString("Game Paused.");
	my_GamePauseTitle.setCharacterSize(55);
	my_GamePauseTitle.setPosition(my_SnakeGameHolder->my_gameWindow->getSize().x / 2, my_SnakeGameHolder->my_gameWindow->getSize().y / 2 );
	my_GamePauseTitle.setOrigin(my_GamePauseTitle.getLocalBounds().width / 2, my_GamePauseTitle.getLocalBounds().height / 2); \

}



void GamePause::InputReader()
{
	sf::Event event;
	while (my_SnakeGameHolder->my_gameWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			my_SnakeGameHolder->my_gameWindow->close();
		}

		//MOVING IN THE WINDOW IS DONE BY PRESSING ARROWS 
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
			{
				std::cout << "Up button is pressed" << std::endl;
				//Pop the pause state
				my_SnakeGameHolder->my_gameStates->PopCurrentGameState();
				break;
			}
			
			}
			
		}

	}
}

void GamePause::UpdateGameState(sf::Time deltaTime)
{


}
void GamePause::Draw()
{
	my_SnakeGameHolder->my_gameWindow->draw(my_GamePauseTitle);
	my_SnakeGameHolder->my_gameWindow->display();
}