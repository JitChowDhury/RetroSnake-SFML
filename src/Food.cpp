#include "Food.h"
#include <cstdlib>
#include<ctime>

Food::Food()
{
	//foodShape.setRadius(10.f);
	//foodShape.setFillColor(sf::Color::Red);
	//
	//foodShape.setPosition(position);

	if (!appleTexture.loadFromFile("assets/apple.png"))
	{
		
	}
	appleSprite.setTexture(appleTexture);
	position = sf::Vector2f(200.f, 100.f);
	appleSprite.setPosition(position);
	appleSprite.setScale(0.5f, 0.5f);

}

void Food::SetRandomPosition(float windowWidth, float windowHeight)
{
	srand(static_cast<unsigned int>(time(0) ^ clock()));
	int posX = (rand() % ((int)windowWidth / 20)) * 20; 
	int posY = (rand() % ((int)windowHeight / 20)) * 20;

	appleSprite.setPosition(sf::Vector2f(posX, posY));
}

void Food::Draw(sf::RenderWindow& window) const
{
	window.draw(appleSprite);
}

sf::Sprite Food::getSprite() const
{
	return appleSprite;
}
sf::FloatRect Food::GetGlobalBounds() const
{
	return appleSprite.getGlobalBounds();
}
