#pragma once
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace Tools
{
	class GameAssetsCommands
	{
	private:
		//MAP TO HOLD TEXTURES/IMAGES AND FONTS FOR THE GAME (SIMILAR TO WHAT UNITY DOES)
		//Map - int and unique_ptr to texture
		std::map<int, std::unique_ptr<sf::Texture>> my_textures;
		//MAP - int and shared_ptr to font
		std::map<int, std::shared_ptr<sf::Font>> my_fonts;


	public:
		GameAssetsCommands();
		~GameAssetsCommands();

		//Const - they do not modify the object
		 
		void LoadTexture(int textureId, const std::string &pathToTexture, bool repeating = false) ;

		const sf::Texture &GetTexture(int textureID) const;
		
		void LoadFont(int fontID, const std::string &pathToFont);


		const sf::Font &GetFont(int fontID) const;
	};
}

