#include "Snake.h"

Snake::Snake():stepSize(20.f),moveTime(0.1f),time(0.f), moveDirection(1,0)
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
		sf::Vector2f position = snakeHead.getPosition();
		snakeHead.setPosition(position + moveDirection *stepSize);
		if (snakeHead.getPosition().x > windowWidth) {
			snakeHead.setPosition(snakeHead.getSize().x / 2, position.y);
		}
		else if (position.x <= 0.f)
		{
			snakeHead.setPosition(windowWidth - snakeHead.getSize().x / 2, position.y);
		}
		else if (position.y > windowHeight)
		{
			snakeHead.setPosition(position.x, snakeHead.getSize().y / 2);
		}
		else if(position.y<=0.f)
		{
			snakeHead.setPosition(position.x, windowHeight - snakeHead.getSize().y / 2);
		}
		time = 0.f;
	}
		
}
	

sf::RectangleShape Snake::GetHeadShape() const
{
	return sf::RectangleShape();
}

void Snake::SetDirection(sf::Vector2f direction)
{

	if (moveDirection.x != -direction.x || moveDirection.y != -direction.y)
	{
		moveDirection = direction;
	}

}

void Snake::draw(sf::RenderWindow& draw) const
{
	draw.draw(snakeHead);
}
