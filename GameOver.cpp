#include "GameOver.h"
#include "GameView.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

GameOver::GameOver(std::shared_ptr<SnakeGameHolder>& SnakeGameHolder)
	: my_SnakeGameHolder(SnakeGameHolder),
	my_RetryButtonIsSelected(true), my_RetryButtonIsPressed(false), my_ExitButtonIsPressed(false), my_ExitButtonIsSelected(false)
{

}
GameOver::~GameOver()
{

}
void GameOver::Initialising()
{
	//TITLE
	my_SnakeGameHolder->my_gameAssets->LoadFont(MENU_FONT, "assets/downloads/fonts/Calligraffitti-Regular.ttf");
	my_GameOverTitle.setFont(my_SnakeGameHolder->my_gameAssets->GetFont(MENU_FONT));
	const sf::Font& font = my_SnakeGameHolder->my_gameAssets->GetFont(MENU_FONT);

	std::cout << "Font memory after get = " << &font << "\n";
	std::cout << "Font Successfully loaded" << std::endl;

	my_GameOverTitle.setString("Game Over");
	my_GameOverTitle.setCharacterSize(55);
	my_GameOverTitle.setPosition(my_SnakeGameHolder->my_gameWindow->getSize().x / 2, my_SnakeGameHolder->my_gameWindow->getSize().y / 2 - 200.f);
	my_GameOverTitle.setOrigin(my_GameOverTitle.getLocalBounds().width / 2, my_GameOverTitle.getLocalBounds().height / 2); \

		//PLAY BUTTON
		my_RetryButton.setFont(my_SnakeGameHolder->my_gameAssets->GetFont(MENU_FONT));

	my_RetryButton.setString("Retry");
	my_RetryButton.setCharacterSize(40);
	my_RetryButton.setPosition(my_SnakeGameHolder->my_gameWindow->getSize().x / 2, my_SnakeGameHolder->my_gameWindow->getSize().y / 2 - 50.f);
	my_RetryButton.setOrigin(my_RetryButton.getLocalBounds().width / 2, my_RetryButton.getLocalBounds().height / 2);


	//EXIT BUTTON
	my_ExitButton.setFont(my_SnakeGameHolder->my_gameAssets->GetFont(MENU_FONT));

	my_ExitButton.setString("Exit");
	my_ExitButton.setCharacterSize(40);
	my_ExitButton.setPosition(my_SnakeGameHolder->my_gameWindow->getSize().x / 2, my_SnakeGameHolder->my_gameWindow->getSize().y / 2 + 50.f);
	my_ExitButton.setOrigin(my_ExitButton.getLocalBounds().width / 2, my_ExitButton.getLocalBounds().height / 2);
}



void GameOver::InputReader()
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
			case sf::Keyboard::Up:
			{
				std::cout << "Up button is pressed" << std::endl;
				if (!my_RetryButtonIsSelected)
				{
					my_RetryButtonIsSelected = true;
					my_ExitButtonIsSelected = false;
				}
				break;
			}
			case sf::Keyboard::Down:
			{
				std::cout << "Down button is pressed" << std::endl;
				if (!my_ExitButtonIsSelected)
				{
					my_RetryButtonIsSelected = false;
					my_ExitButtonIsSelected = true;
				}
				break;
			}
			//Check if key was pressend enter
			case sf::Keyboard::Enter:
			{
				//just in case
				my_RetryButtonIsPressed = false;
				my_ExitButtonIsPressed = false;
				if (my_RetryButtonIsSelected == true)
				{
					my_RetryButtonIsPressed = true;
				}
				else if (my_ExitButtonIsSelected == true)
				{
					my_ExitButtonIsPressed = true;
				}
				break;
			}
			}
		}

	}
}

void GameOver::UpdateGameState(sf::Time deltaTime)
{

	//highlighting the selected option
	if (my_RetryButtonIsSelected == true)
	{
		my_RetryButton.setFillColor(sf::Color::Magenta);
		my_ExitButton.setFillColor(sf::Color::White);
	}
	else if (my_ExitButtonIsSelected == true)
	{
		my_ExitButton.setFillColor(sf::Color::Magenta);
		my_RetryButton.setFillColor(sf::Color::White);
	}
	if (my_RetryButtonIsPressed)
	{
		std::cout << "Retrying the game..." << std::endl;
		my_SnakeGameHolder->my_gameStates->AddGameState(std::make_unique<GameView>(my_SnakeGameHolder), true);
	}
	else if (my_ExitButtonIsPressed)
	{
		std::cout << "Closing the game..." << std::endl;
		my_SnakeGameHolder->my_gameWindow->close();
	}

}
void GameOver::Draw()
{
	my_SnakeGameHolder->my_gameWindow->clear(sf::Color::Black);
	my_SnakeGameHolder->my_gameWindow->draw(my_GameOverTitle);
	my_SnakeGameHolder->my_gameWindow->draw(my_RetryButton);
	my_SnakeGameHolder->my_gameWindow->draw(my_ExitButton);
	my_SnakeGameHolder->my_gameWindow->display();
}