#pragma once

#include <stack>
#include <memory>

#include "GameState.h"
namespace Tools 
{
	class GameStateManager 
	{
	private:
		//STACK TO STORE DIFFERENT GAME STATES
		std::stack<std::unique_ptr<GameState>> my_gameStateStack; 
		//UNIQUE PTR THAT STORES NEW STATE ADDED TO THE STACK, SO THAT NO NEW STATE WHILE STATE IS EXECUTING
		std::unique_ptr<GameState> my_newGameState;

		bool my_add;
		bool my_replace;
		bool my_remove;



	public:
		GameStateManager();
		~GameStateManager();
	

		//METHODS TO ADD NEW GAMESTATE TO THE STACK, WE WANT TO BE ABLE TO MODIFY THE STACK - POPCURRENT AND READGAMESTATECHANGE
		void AddGameState(std::unique_ptr<GameState> stateToADD, bool replaceAnotherState = false);
		void PopCurrentGameState();
		void StateChange();
		//METHOD TO GET GAMESTATE
		std::unique_ptr<GameState>& GetCurrentGameState();
	};

}




