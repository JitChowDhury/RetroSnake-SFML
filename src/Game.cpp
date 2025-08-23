#include<iostream>
#include "Game.h"
#include <filesystem>



Game::Game():WINDOW_WIDTH{800},WINDOW_HEIGHT{600}, window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Snake Game"), deltaTime(0.f),score(0),retries(0),maxRetry(100),isGameover(false)
{

    window.setFramerateLimit(60);
    food.SetRandomPosition(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!backgroundTexture.loadFromFile("assets/background.png"))
    {

    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(0.5208f, 0.5859f);
    
 

    do {
        food.SetRandomPosition(WINDOW_WIDTH, WINDOW_HEIGHT);
        retries++;
        if (retries >= maxRetry)
        {
            food.SetRandomPosition(200.f, 200.f);
            break;
        }
    } while (isPositionOnSnake(food.getSprite().getPosition(), snake));

    if (!font.loadFromFile("assets/Fonts/arial.ttf"))
    {
        std::filesystem::path cwd = std::filesystem::current_path();
        std::cout << "Current working directory: " << cwd << "\n";
        std::cout << "Failed to load file" << std::endl;
        

    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    scoreText.setString("Score: 0");

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(300.f, 280.f);
    gameOverText.setString("Game Over!");


    
}



void Game::Update()
{
    if (isGameover) return;
    deltaTime = clock.restart().asSeconds();
    snake.Update(deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::Vector2f headPos = snake.GetHeadPosition();
    if (headPos.x < 0.f || headPos.x >= 800.f || headPos.y < 0.f || headPos.y >= 600.f) {
        isGameover = true;
        gameOverText.setString("Game Over!");
    }

    for (const auto& bodyPos : snake.getBodyPositions()) {
        if (headPos == bodyPos) {
            isGameover = true;
            gameOverText.setString("Game Over!");
            break;
        }
    }

    if (snake.GetGlobalBounds().intersects(food.GetGlobalBounds()))
    {
        snake.grow();
        score += 1;
        scoreText.setString("Score: " + std::to_string(score));
        retries = 0;
        do {
            food.SetRandomPosition(WINDOW_WIDTH, WINDOW_HEIGHT);
            retries++;
            if (retries >= maxRetry) {
                food.SetRandomPosition(200.f, 200.f); // Fallback
                break;
            }
        } while (isPositionOnSnake(food.getSprite().getPosition(), snake));
    }
   
}

void Game::HandleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::W)
            {
                snake.SetDirection(sf::Vector2f(0.f, -1.f));
            }
            if (event.key.code == sf::Keyboard::S)
            {
                snake.SetDirection(sf::Vector2f(0.f, 1.f));
            }
            if (event.key.code == sf::Keyboard::A)
            {
                snake.SetDirection(sf::Vector2f(-1.f, 0.f));
            }
            if (event.key.code == sf::Keyboard::D)
            {
                snake.SetDirection(sf::Vector2f(1.f, 0.f));

            }
            if (event.key.code == sf::Keyboard::Space)
            {
                snake.grow();
            }
            if (event.key.code == sf::Keyboard::R)
            {
                isGameover = false;
            }
              
        }
    }
}

void Game::Render()
{

    window.clear();
    window.draw(backgroundSprite);
    food.Draw(window);
    snake.draw(window);
    window.draw(scoreText);
    if (isGameover) {
        window.draw(gameOverText);
    }
    window.display();
}

void Game::Run()
{

    while (window.isOpen())
    {
        Update();
        HandleEvents();
        Render();

    }
}



bool Game::isPositionOnSnake(const sf::Vector2f& position, const Snake& snake)
{
    if (position == snake.GetHeadPosition())
    {
        return true;
    }
    for (const auto& bodypos : snake.getBodyPositions())
    {
        if (position == bodypos)
        {
            return true;
        }
    }

    return false;
}

