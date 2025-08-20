#include <SFML/Graphics.hpp>
class Snake
{
private:
	sf::RectangleShape snakeHead;
	sf::Vector2f position;
	sf::Vector2f direction;
	float time;
	float moveTime;
	sf::Vector2f moveDirection;
	
	float stepSize;
public:
	Snake();
	void Update(float deltaTime, float windowWidth, float windowHeight);
	sf::RectangleShape GetHeadShape() const;
	void SetDirection(sf::Vector2f direction);
	void draw(sf::RenderWindow& draw) const;
};