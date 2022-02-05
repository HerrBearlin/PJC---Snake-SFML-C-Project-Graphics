#include "SnakeGame.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Window/Event.hpp"
#include "MainMenu.h"

SnakeGame::SnakeGame() : my_SnakeGameHolder(std::make_shared<SnakeGameHolder>())
{
	//CREATING WINDOW FOR THE GAME
	my_SnakeGameHolder->my_gameWindow->create(sf::VideoMode(480, 480), "SFML Snake Game", sf::Style::Close);
	//Add first state to my_gameStates
    my_SnakeGameHolder->my_gameStates->AddGameState(std::make_unique<MainMenu>(my_SnakeGameHolder));
}
SnakeGame::~SnakeGame()
{

}

void SnakeGame::RunGame() 
{
    //Clock starts as soon as it is created!! 
    sf::Clock clock;
    sf::Time dtime = sf::Time::Zero;

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (my_SnakeGameHolder->my_gameWindow->isOpen())
    {
        dtime += clock.restart();
        
        //Same stuff as in QuantumBridge -> Limiting number of FPS to 60 on all machines
        while (dtime > framePerSecond) 
        {
            dtime -= framePerSecond;
            
            my_SnakeGameHolder->my_gameStates->StateChange();
            my_SnakeGameHolder->my_gameStates->GetCurrentGameState()->InputReader();
            my_SnakeGameHolder->my_gameStates->GetCurrentGameState()->UpdateGameState(framePerSecond);
            my_SnakeGameHolder->my_gameStates->GetCurrentGameState()->Draw();

          

        }
      
    }

}