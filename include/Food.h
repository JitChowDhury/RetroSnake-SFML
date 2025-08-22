#pragma once
#include <SFML/Graphics.hpp>

class Food
{
private:
	sf::CircleShape foodShape;
	sf::Vector2f position;
public:
	Food();
	void SetRandomPosition(float windowWidth, float windowHeight);
	void Draw(sf::RenderWindow& window)const;
	sf::CircleShape getShape() const;
	sf::FloatRect GetGlobalBounds() const;
};