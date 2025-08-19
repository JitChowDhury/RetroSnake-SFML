#include "Snake.h"

Snake::Snake():stepSize(20.f),moveTime(0.1f),time(0.f)
{
	snakeHead.setSize(sf::Vector2f(20, 20));
	snakeHead.setOrigin(10, 10);
	snakeHead.setPosition(100, 100);
	snakeHead.setFillColor(sf::Color::Green);

}

void Snake::Update(float deltaTime, float windowWidth, float windowHeight)
{
	time += deltaTime;
	if (time > moveTime)
	{
		snakeHead.setPosition(snakeHead.getPosition() + sf::Vector2f(1, 0)*stepSize);
		if (snakeHead.getPosition().x > windowWidth) {
			snakeHead.setPosition(snakeHead.getSize().x / 2, snakeHead.getPosition().y);
		}
		time = 0.f;
	}
		
}
	

sf::RectangleShape Snake::GetHeadShape() const
{
	return sf::RectangleShape();
}

void Snake::draw(sf::RenderWindow& draw) const
{
	draw.draw(snakeHead);
}
