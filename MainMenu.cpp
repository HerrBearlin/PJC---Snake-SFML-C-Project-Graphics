#include "MainMenu.h"
#include "GameView.h"
#include <iostream>
#include <SFML/Window/Event.hpp>

//providing info for the MainMenu
MainMenu::MainMenu(std::shared_ptr<SnakeGameHolder> &SnakeGameHolder) 
	: my_SnakeGameHolder(SnakeGameHolder),
	 my_PlayButtonIsSelected(true), my_PlayButtonIsPressed(false), my_ExitButtonIsPressed(false), my_ExitButtonIsSelected(false)
{

}
MainMenu::~MainMenu()
{

}


void MainMenu::Initialising()
{
	//TITLE
	my_SnakeGameHolder->my_gameAssets->LoadFont(MENU_FONT, "assets/downloads/fonts/Calligraffitti-Regular.ttf");
	my_GameTitle.setFont(my_SnakeGameHolder->my_gameAssets->GetFont(MENU_FONT));
	const sf::Font&  font = my_SnakeGameHolder->my_gameAssets->GetFont(MENU_FONT);

	std::cout << "Font memory after get = " << & font << "\n";
	std::cout << "Font Successfully loaded" << std::endl;

	my_GameTitle.setString("SFML Snake Game!");
	my_GameTitle.setCharacterSize(55);
	my_GameTitle.setPosition(my_SnakeGameHolder->my_gameWindow->getSize().x / 2, my_SnakeGameHolder->my_gameWindow->getSize().y / 2 - 200.f);
	my_GameTitle.setOrigin(my_GameTitle.getLocalBounds().width / 2, my_GameTitle.getLocalBounds().height / 2 ); \

	//PLAY BUTTON
	my_PlayButton.setFont(my_SnakeGameHolder->my_gameAssets->GetFont(MENU_FONT));

	my_PlayButton.setString("Play");
	my_PlayButton.setCharacterSize(40);
	my_PlayButton.setPosition(my_SnakeGameHolder->my_gameWindow->getSize().x / 2, my_SnakeGameHolder->my_gameWindow->getSize().y / 2 - 50.f);
	my_PlayButton.setOrigin(my_PlayButton.getLocalBounds().width / 2, my_PlayButton.getLocalBounds().height / 2 );


	//EXIT BUTTON
	my_ExitButton.setFont(my_SnakeGameHolder->my_gameAssets->GetFont(MENU_FONT));

	my_ExitButton.setString("Exit");
	my_ExitButton.setCharacterSize(40);
	my_ExitButton.setPosition(my_SnakeGameHolder->my_gameWindow->getSize().x / 2, my_SnakeGameHolder->my_gameWindow->getSize().y / 2 + 50.f);
	my_ExitButton.setOrigin(my_ExitButton.getLocalBounds().width / 2, my_ExitButton.getLocalBounds().height / 2 );
}



void MainMenu::InputReader()
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
					if (!my_PlayButtonIsSelected)
					{
						my_PlayButtonIsSelected = true;
						my_ExitButtonIsSelected = false;
					}
					break;
				}
				case sf::Keyboard::Down:
				{
					std::cout << "Down button is pressed" << std::endl;
					if (!my_ExitButtonIsSelected)
					{
						my_PlayButtonIsSelected = false;
						my_ExitButtonIsSelected = true;
					}
					break;
				}
				//Check if key was pressend enter
				case sf::Keyboard::Enter:
				{
					//just in case
					my_PlayButtonIsPressed = false;
					my_ExitButtonIsPressed = false;
					if (my_PlayButtonIsSelected == true)
					{
						my_PlayButtonIsPressed = true;
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

void MainMenu::UpdateGameState(sf::Time deltaTime)
{
	
	//highlighting the selected option
	if (my_PlayButtonIsSelected == true)
	{
		my_PlayButton.setFillColor(sf::Color::Magenta);
		my_ExitButton.setFillColor(sf::Color::White);
	}
	else if (my_ExitButtonIsSelected == true)
	{
		my_ExitButton.setFillColor(sf::Color::Magenta);
		my_PlayButton.setFillColor(sf::Color::White);
	}
	if (my_PlayButtonIsPressed)
	{
		my_SnakeGameHolder->my_gameStates->AddGameState(std::make_unique<GameView>(my_SnakeGameHolder), true);
	}
	else if (my_ExitButtonIsPressed)
	{
		std::cout << "Closing the game..." << std::endl;
		my_SnakeGameHolder->my_gameWindow->close();
	}
	
}
void MainMenu::Draw()
{
	my_SnakeGameHolder->my_gameWindow->clear(sf::Color::Black);
	my_SnakeGameHolder->my_gameWindow->draw(my_GameTitle);
	my_SnakeGameHolder->my_gameWindow->draw(my_PlayButton);
	my_SnakeGameHolder->my_gameWindow->draw(my_ExitButton);
	my_SnakeGameHolder->my_gameWindow->display();
}