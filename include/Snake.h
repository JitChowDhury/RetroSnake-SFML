#include <SFML/Graphics.hpp>
#include <vector>
class Snake
{
private:
	sf::RectangleShape snakeHead;
	std::vector<sf::RectangleShape>body;
	sf::Vector2f position;
	sf::Vector2f direction;
	float time;
	float moveTime;
	sf::Vector2f moveDirection;
	
	float stepSize;
public:
	Snake();
	void Update(float deltaTime, float windowWidth, float windowHeight);
	void SetDirection(sf::Vector2f direction);
	void draw(sf::RenderWindow& draw) const;
	void grow();


};