#include "Game.h"

Game::Game():window(sf::VideoMode({ 800, 600 }), "Snake Game"),deltaTime(0.f)
{

    window.setFramerateLimit(60);
}



void Game::Update()
{
    deltaTime = clock.restart().asSeconds();
    snake.Update(deltaTime);
    snake.Wrap(800, 600);
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

