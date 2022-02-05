#include "GameView.h"
#include "GamePause.h"
#include <SFML/Window/Event.hpp>


#include <stdlib.h>
#include <time.h>
#include "GameOver.h"


GameView::GameView(std::shared_ptr<SnakeGameHolder>& SnakeGameHolder)
	: my_SnakeGameHolder(SnakeGameHolder), my_SnakeDirection({ 16.f, 0.f }), my_ElapsedTime(sf::Time::Zero), my_Score(0)
{
	//different set of random numbers every time -> pass current time to s rank; calling time function with null ptr
	srand(time(nullptr));
}
GameView::~GameView()
{
}



void GameView::Initialising()
{

	//TEXTURES 
	my_SnakeGameHolder->my_gameAssets->LoadTexture(GRASS_BACKGROUND_SPRITE, "assets/downloads/sprites/GrassBackground.png", true);
	my_SnakeGameHolder->my_gameAssets->LoadTexture(BORDER_SPRITE, "assets/downloads/sprites/PixelWall.png");
	my_SnakeGameHolder->my_gameAssets->LoadTexture(POINT_SPRITE, "assets/downloads/sprites/PixelStrawberry.png", true);
		//load snake
	my_SnakeGameHolder->my_gameAssets->LoadTexture(SNAKE_SPRITE, "assets/downloads/sprites/PixelSnakeHead.png");

	my_Background.setTexture(my_SnakeGameHolder->my_gameAssets->GetTexture(GRASS_BACKGROUND_SPRITE));
		//fill the whole window
	my_Background.setTextureRect(my_SnakeGameHolder->my_gameWindow->getViewport(my_SnakeGameHolder->my_gameWindow->getDefaultView()));

	for (auto& border : my_Borders)
	{
		border.setTexture(my_SnakeGameHolder->my_gameAssets->GetTexture(BORDER_SPRITE));
	}



		//INT RECT REPRESETNTING RECTANGE (RECTLEFT CORNER, RECTTOP CORNER, RECTWIDTH, RECTHEIGHT) 16-THICKNESS OF WALLS
	my_Borders[0].setTextureRect({ 0, 0, 480, 16 }); //top wall

	my_Borders[1].setTextureRect({ 0, 0, 480, 16 }); //bottom wall
	my_Borders[1].setPosition(0, 480 - 16);

	my_Borders[2].setTextureRect({ 0, 0, 16, 480 }); //left wall

	my_Borders[3].setTextureRect({ 0, 0, 16, 480 }); // right wall
	my_Borders[3].setPosition(480 - 16, 0);


	//SCORE FONT AND POSITION
	my_ScoreText.setFont(my_SnakeGameHolder->my_gameAssets->GetFont(MENU_FONT));
	my_ScoreText.setString("Score: " + std::to_string(my_Score));
	my_ScoreText.setCharacterSize(17);
	my_ScoreText.setFillColor(sf::Color::White);


	//POINT TEXTURE AND POSITION
	my_Point.setTexture(my_SnakeGameHolder->my_gameAssets->GetTexture(POINT_SPRITE));
	my_Point.setPosition(my_SnakeGameHolder->my_gameWindow->getSize().x / 2, my_SnakeGameHolder->my_gameWindow->getSize().y / 2);

	//SNAKE TEXTURE AND POSITION
	my_Snake.Initialise(my_SnakeGameHolder->my_gameAssets->GetTexture(SNAKE_SPRITE));

	
}

void GameView::InputReader()
{
	sf::Event event;
	while (my_SnakeGameHolder->my_gameWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			my_SnakeGameHolder->my_gameWindow->close();
		}
		//processing user input
		else if (event.type == sf::Event::KeyPressed)
		{
			sf::Vector2f newSnakeDirection = my_SnakeDirection;
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				newSnakeDirection = { 0.f, -16.f };
				break;
			case sf::Keyboard::Down:
				newSnakeDirection = { 0.f, 16.f };
				break;
			case sf::Keyboard::Left:
				newSnakeDirection = { -16.f, 0.f };
				break;
			case sf::Keyboard::Right:
				newSnakeDirection = { 16.f, 0.f };
				break;
			case sf::Keyboard::Space :
				my_SnakeGameHolder->my_gameStates->AddGameState(std::make_unique<GamePause>(my_SnakeGameHolder));
				break;
			}


			//abs command - absolute value (NICE)
			//WE CANNOT DO 180 DEGREES TURN
			if (std::abs(my_SnakeDirection.x) != std::abs(newSnakeDirection.x) || std::abs(my_SnakeDirection.y) != std::abs(newSnakeDirection.y))
			{
				my_SnakeDirection = newSnakeDirection;
			}
		}
	}
}

void GameView::UpdateGameState(sf::Time deltaTime)
{
	my_ElapsedTime += deltaTime;
	//make sure it is not tooo speeedy
	if (my_ElapsedTime.asSeconds() > 0.3)
	{
		//my_Snake.Move(my_SnakeDirection);

		for (auto& border : my_Borders) 
		{
			if (my_Snake.CollidingWith(border))
			{
				//GAME OVER
				my_SnakeGameHolder->my_gameStates->AddGameState(std::make_unique<GameOver>(my_SnakeGameHolder), true);
				break;
			}
		}

		if (my_Snake.BitingTail())
		{
			my_SnakeGameHolder->my_gameStates->AddGameState(std::make_unique<GameOver>(my_SnakeGameHolder), true);
		}

		if (my_Snake.CollidingWith(my_Point))
		{
			my_Snake.GrowTail(my_SnakeDirection);
			my_Score += 1;
			my_ScoreText.setString("Score : " + std::to_string(my_Score));
			int posX = 0, posY = 0;
			posX = rand() % ((my_SnakeGameHolder->my_gameWindow->getSize().x + 32) - 32);
			posY = rand() % ((my_SnakeGameHolder->my_gameWindow->getSize().y + 32) - 32);
			
			my_Point.setPosition(posX, posY);
		}
		else
		{
			//we dont want to move while snake is growing cause it breaks the game
			my_Snake.Move(my_SnakeDirection);
		}
		

		my_ElapsedTime = sf::Time::Zero;
	}
}

void GameView::Draw()
{
	my_SnakeGameHolder->my_gameWindow->clear();
	my_SnakeGameHolder->my_gameWindow->draw(my_Background);
	for (auto& border : my_Borders) 
	{
		my_SnakeGameHolder->my_gameWindow->draw(border);
	}
	my_SnakeGameHolder->my_gameWindow->draw(my_ScoreText);
	my_SnakeGameHolder->my_gameWindow->draw(my_Point);
	my_SnakeGameHolder->my_gameWindow->draw(my_Snake);

	my_SnakeGameHolder->my_gameWindow->display();
}

void GameView::Pause()
{

}

void GameView::Start()
{

}