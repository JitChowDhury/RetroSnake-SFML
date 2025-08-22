#pragma once
#include <SFML/Graphics.hpp>

class Food
{
private:
	//sf::CircleShape foodShape;
	sf::Vector2f position;
	sf::Texture appleTexture;
	sf::Sprite appleSprite;
public:
	Food();
	void SetRandomPosition(float windowWidth, float windowHeight);
	void Draw(sf::RenderWindow& window)const;
	sf::Sprite getSprite() const;
	sf::FloatRect GetGlobalBounds() const;
};