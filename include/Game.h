#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"

class Game
{
private:
	const unsigned int WINDOW_WIDTH;
	const unsigned int WINDOW_HEIGHT;

	sf::RenderWindow window;
	Snake snake;
	sf::Clock clock;
	float deltaTime;
	Food food;
	sf::Font font;
	sf::Text scoreText;
	int score;
	int retries ;
	const int maxRetry;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;


	void Update();
	void HandleEvents();
	void Render();
public:
	Game();
	void Run();
	bool isPositionOnSnake(const sf::Vector2f& position, const Snake& snake);
};