#include <SFML/Graphics.hpp>
class Snake
{
private:
	sf::RectangleShape snakeHead;
	sf::Vector2f position;
	sf::Vector2f direction;
	float time;
	float moveTime;
	
	float stepSize;
public:
	Snake();
	void Update(float deltaTime);
	void Wrap(float windowWidth, float windowHeight);
	sf::RectangleShape GetHeadShape() const;

	void draw(sf::RenderWindow& draw) const;
};