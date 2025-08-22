#include "Snake.h"

Snake::Snake():stepSize(20.f),moveTime(0.1f),time(0.f), moveDirection(1,0)
{
	snakeHead.setSize(sf::Vector2f(20.f, 20.f));
	snakeHead.setOrigin(10.f, 10.f);
	position = sf::Vector2f(100.f, 100.f);
	snakeHead.setPosition(position);
	snakeHead.setFillColor(sf::Color::Green);

	sf::RectangleShape bodySegment;
	bodySegment.setSize(sf::Vector2f(20.f, 20.f));
	bodySegment.setFillColor(sf::Color::White);
	bodySegment.setOrigin(10.f, 10.f);
	bodySegment.setPosition(position - sf::Vector2f(stepSize, 0.f));
	body.push_back(bodySegment);

}

void Snake::Update(float deltaTime, float windowWidth, float windowHeight)
{
	time += deltaTime;
	if (time > moveTime)
	{
		sf::Vector2f prevPosition = position;
		position += moveDirection * stepSize;
		snakeHead.setPosition(position);

		// Update body segments
		for (size_t i = 0; i < body.size(); ++i) {
			sf::Vector2f temp = body[i].getPosition();
			body[i].setPosition(prevPosition);
			prevPosition = temp;
		}
		
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
		position = snakeHead.getPosition();
		time = 0.f;
	}
		
}
	



void Snake::SetDirection(sf::Vector2f direction)
{

	if (moveDirection.x != -direction.x || moveDirection.y != -direction.y)
	{
		moveDirection = direction;
	}

}

void Snake::grow() {
	sf::RectangleShape newSegment;
	newSegment.setSize(sf::Vector2f(20.f, 20.f));
	newSegment.setFillColor(sf::Color::White);
	newSegment.setOrigin(10.f, 10.f);
	//newSegment.setOutlineColor(sf::Color::Red);
	//newSegment.setOutlineThickness(1.f);
	// Place new segment at the tail's position
	sf::Vector2f tailPosition = body.empty() ? position - moveDirection * stepSize : body.back().getPosition();
	newSegment.setPosition(tailPosition);
	body.push_back(newSegment);
}

void Snake::draw(sf::RenderWindow& window) const
{
	window.draw(snakeHead);
	for (auto& segment : body)
	{
		window.draw(segment);
	}
}
