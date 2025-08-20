#include<iostream>
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

