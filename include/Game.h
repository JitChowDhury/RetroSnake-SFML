#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class Game
{
private:
	const unsigned int WINDOW_WIDTH;
	const unsigned int WINDOW_HEIGHT;

	sf::RenderWindow window;
	Snake snake;
	sf::Clock clock;
	float deltaTime;


	void Update();
	void HandleEvents();
	void Render();
public:
	Game();
	void Run();
};