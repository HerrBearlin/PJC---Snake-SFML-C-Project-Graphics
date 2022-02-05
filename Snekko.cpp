#include "Snekko.h"
Snekko::Snekko() : my_SnakeBody(std::list<sf::Sprite>(4)) //01234[] 4-head 0 -tail
{
	my_SnakeHead = --my_SnakeBody.end();
	my_SnakeTail = my_SnakeBody.begin();
}
Snekko::~Snekko()
{

}


void Snekko::Initialise(const sf::Texture& texture)
{
	float x = 64.f;
	for (auto& tailpart : my_SnakeBody)
	{
		tailpart.setTexture(texture);
		tailpart.setPosition({ x, 16.f });
		x += 16.f; //all sprites are 16x16
	}
}
void Snekko::Move(const sf::Vector2f& direction)
{
	my_SnakeTail->setPosition(my_SnakeHead->getPosition() + direction);
	my_SnakeHead = my_SnakeTail;
	++my_SnakeTail;

	if (my_SnakeTail == my_SnakeBody.end())
	{
		my_SnakeTail = my_SnakeBody.begin();
	}
}

bool Snekko::CollidingWith(const sf::Sprite& something) const
{
	return something.getGlobalBounds().intersects(my_SnakeHead->getGlobalBounds());
}
bool Snekko::BitingTail() const
{
	bool sth = false;

	//we must add bodyPart !=my_SnakeBody.end() because it would return always truu
	for (auto bodyPart = my_SnakeBody.begin(); bodyPart != my_SnakeBody.end(); ++bodyPart)
	{
		if (my_SnakeHead != bodyPart)
		{
			sth = CollidingWith(*bodyPart);
			if (sth)
			{
				break;
			}
		}
	}
	return sth;
}
void Snekko::GrowTail(const sf::Vector2f& direction)
{
	sf::Sprite newTailPart;

	//we can get texture from any point of the snakebody :O

	newTailPart.setTexture(*(my_SnakeBody.begin()->getTexture()));
	newTailPart.setPosition(my_SnakeHead->getPosition() + direction);

	//adding new part just after the head - insert returns an iterator to the inserted data
	//after adding the piece, head of the snake will be the new piece
	my_SnakeHead = my_SnakeBody.insert(++my_SnakeHead, newTailPart);
}

void Snekko::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	for (auto& tailpart : my_SnakeBody)
	{
		target.draw(tailpart);
	}
}