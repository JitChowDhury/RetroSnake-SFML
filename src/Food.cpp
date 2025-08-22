#include "Food.h"
#include <cstdlib>
#include<ctime>

Food::Food()
{
	foodShape.setRadius(10.f);
	foodShape.setFillColor(sf::Color::Red);
	position = sf::Vector2f(200.f, 100.f);
	foodShape.setPosition(position);

}

void Food::SetRandomPosition(float windowWidth, float windowHeight)
{
	srand(static_cast<unsigned int>(time(0) ^ clock()));
	int posX = (rand() % ((int)windowWidth / 20)) * 20; 
	int posY = (rand() % ((int)windowHeight / 20)) * 20;

	foodShape.setPosition(sf::Vector2f(posX, posY));
}

void Food::Draw(sf::RenderWindow& window) const
{
	window.draw(foodShape);
}

sf::CircleShape Food::getShape() const
{
	return foodShape;
}
sf::FloatRect Food::GetGlobalBounds() const
{
	return foodShape.getGlobalBounds();
}
