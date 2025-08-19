#include "Game.h"

Game::Game():WINDOW_WIDTH{800},WINDOW_HEIGHT{600}, window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Snake Game"), deltaTime(0.f)
{

    window.setFramerateLimit(60);
}



void Game::Update()
{
    deltaTime = clock.restart().asSeconds();
    snake.Update(deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT);
   
}

void Game::HandleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void Game::Render()
{

    window.clear();
    snake.draw(window);
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

