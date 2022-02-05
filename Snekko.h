#pragma once


#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


class Snekko : public sf::Drawable
{

private:
	std::list<sf::Sprite> my_SnakeBody;

	std::list<sf::Sprite>::iterator my_SnakeHead;
	std::list<sf::Sprite>::iterator my_SnakeTail;
public:
	Snekko();
	~Snekko();


	void Initialise(const sf::Texture &texture);
	void Move(const sf::Vector2f& direction);
	bool CollidingWith(const sf::Sprite& something) const;
	bool BitingTail() const;
	void GrowTail(const sf::Vector2f& direction);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

