#include "GameAssetsCommands.h"
#include <iostream>


Tools::GameAssetsCommands::GameAssetsCommands()
{
}
Tools::GameAssetsCommands::~GameAssetsCommands()
{
}


void Tools::GameAssetsCommands::LoadTexture(int textureID, const std::string &pathToTexture, bool repeating) 
{
	//creating new texture using makeunique
	auto texture = std::make_unique< sf::Texture>();

	if (texture->loadFromFile(pathToTexture))
	{
		//should it repeat?
		texture->setRepeated(repeating);
		my_textures[textureID] = std::move(texture);
		std::cout << "Texture successfully loaded!!" << std::endl;
	}
	else {
		std::cout << "texture prioblem" << std::endl;
	}
	

};

const sf::Texture &Tools::GameAssetsCommands::GetTexture(int textureID) const
{
	std::cout << "Texture Got" << std::endl;
	return *(my_textures.at(textureID).get());

}

void Tools::GameAssetsCommands::LoadFont(int fontID, const std::string &pathToFont) 
{
	auto font = std::make_unique< sf::Font>();

	if (font->loadFromFile(pathToFont))
	{
		std::cout << "Font successfully loaded!!"<< std::endl;
		my_fonts[fontID] = std::move(font);
		std::cout << "Font memory = " << &my_fonts[fontID] << "\n";
	}
	

}


const sf::Font &Tools::GameAssetsCommands::GetFont(int fontID) const
{
	std::cout << "Font Got" << std::endl;
	return *(my_fonts.at(fontID).get());
	
}