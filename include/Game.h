#pragma once
#include <SFML/Graphics.hpp>
#include <SFMl/Audio.hpp>
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
	int score;
	int retries ;
	const int maxRetry;
	bool isGameover;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Text scoreText;
	sf::Text gameOverText;
	sf::Music mainMusic;

	sf::SoundBuffer eatBuffer;
	sf::SoundBuffer gameoverBuffer;

	sf::Sound eatSound;
	sf::Sound gameOverSound;


	void Update();
	void HandleEvents();
	void Render();
public:
	Game();
	void Run();
	bool isPositionOnSnake(const sf::Vector2f& position, const Snake& snake);
};