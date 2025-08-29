#include<iostream>
#include "Game.h"
#include <filesystem>



Game::Game():WINDOW_WIDTH{800},WINDOW_HEIGHT{600}, window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Snake Game"), deltaTime(0.f),score(0),retries(0),maxRetry(100),isGameover(false),currentState(GameState::MENU)
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

    if (!font.loadFromFile("assets/Fonts/Planes_ValMore.ttf"))
    {
        std::filesystem::path cwd = std::filesystem::current_path();
        std::cout << "Current working directory: " << cwd << "\n";
        std::cout << "Failed to load file" << std::endl;
        

    }
    if (!mainMusic.openFromFile("assets/bgm.wav"))
    {
        std::cout << "Error loading music file!\n";
    }

    if (!eatBuffer.loadFromFile("assets/food.wav"))
    {
        std::cout << "food sound failed to load!" << std::endl;
    }

    if (!gameoverBuffer.loadFromFile("assets/gameover.wav"))
    {
        std::cout << "gameover sound failed to load!" << std::endl;

    }

    eatSound.setBuffer(eatBuffer);
    gameOverSound.setBuffer(gameoverBuffer);

    mainMusic.setLoop(true);
    mainMusic.setVolume(10.f);
    mainMusic.play();

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    scoreText.setString("Score: 0");

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(320.f, 280.f);
    gameOverText.setString("Game Over!");


    startText.setFont(font);
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(370.f, 300.f);
    startText.setString("Start");


    restartText.setFont(font);
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(350.f, 380.f);
    restartText.setString("Restart");


    fpsText.setFont(font);
    fpsText.setCharacterSize(18);
    fpsText.setFillColor(sf::Color::Yellow);
    fpsText.setPosition(WINDOW_WIDTH - 100.f, 10.f); 
    fpsText.setString("FPS: 0");

    titleText.setFont(font);
    titleText.setCharacterSize(70);
    titleText.setString("SNAKEEE");

    // Get bounding box of the text
    sf::FloatRect textBounds = titleText.getLocalBounds();

    // Set origin to the center of the text
    titleText.setOrigin(textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f);

    // Position it at the middle top (centered horizontally, y=50 for some spacing)
    titleText.setPosition(WINDOW_WIDTH / 2.f, 90.f);

    startButton.setSize(sf::Vector2f(200.f, 80.f));
    startButton.setPosition(300.f, 280.f);
    startButton.setFillColor(sf::Color(200, 0, 0));

    restartButton.setSize(sf::Vector2f(200.f, 80.f));
    restartButton.setPosition(300.f, 360.f);
    restartButton.setFillColor(sf::Color(200, 0, 0));

    
}



void Game::Update()
{
    if (isGameover) return;
    if (currentState != GameState::PLAYING)return;

    deltaTime = clock.restart().asSeconds();
    snake.Update(deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::Vector2f headPos = snake.GetHeadPosition();
    if (headPos.x < 0.f || headPos.x >= 800.f || headPos.y < 0.f || headPos.y >= 600.f) {
        isGameover = true;
        gameOverSound.play();
        mainMusic.stop();
        currentState = GameState::GAMEOVER;
        gameOverText.setString("Game Over!");
    }

    sf::FloatRect headBounds = snake.GetGlobalBounds();
    for (size_t i = 1; i < snake.getBodyPositions().size(); i++) {
        sf::Vector2f pos = snake.getBodyPositions()[i];
        sf::FloatRect bodyBounds(pos.x, pos.y, 20.f, 20.f);
        if (headBounds.intersects(bodyBounds)) {
            isGameover = true;
            currentState = GameState::GAMEOVER;
            gameOverSound.play();
            mainMusic.stop();
            break;
        }
    }

    if (snake.GetGlobalBounds().intersects(food.GetGlobalBounds()))
    {
        snake.grow();
        eatSound.play();
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
    if (deltaTime > 0.f) {
        int fps = static_cast<int>(1.f / deltaTime);

        // Update only once per second
        if (fpsClock.getElapsedTime().asSeconds() >= 1.f) {
            currentFps = fps;
            fpsText.setString("FPS: " + std::to_string(currentFps));
            fpsClock.restart();
        }


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
        else if (event.type == sf::Event::KeyPressed && currentState == GameState::PLAYING)
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
                snake.snakeReset();
                mainMusic.play();
                score = 0;
                scoreText.setString("Score: 0");

                do {
                    food.SetRandomPosition(WINDOW_WIDTH, WINDOW_HEIGHT);
                    retries++;
                    if (retries >= maxRetry)
                    {
                        food.SetRandomPosition(200.f, 200.f);
                        break;
                    }
                } while (isPositionOnSnake(food.getSprite().getPosition(), snake));
            }

        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (currentState == GameState::MENU)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (startButton.getGlobalBounds().contains(mousePos))
                {
                    currentState = GameState::PLAYING;
                }
            }
            else if (currentState == GameState::GAMEOVER) {
                // Check if Restart button clicked
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (restartButton.getGlobalBounds().contains(mousePos)) {
                    isGameover = false;
                    snake.snakeReset();
                    mainMusic.play();
                    score = 0;
                    scoreText.setString("Score: 0");

                    retries = 0;
                    do {
                        food.SetRandomPosition(WINDOW_WIDTH, WINDOW_HEIGHT);
                        retries++;
                        if (retries >= maxRetry) {
                            food.SetRandomPosition(200.f, 200.f);
                            break;
                        }
                    } while (isPositionOnSnake(food.getSprite().getPosition(), snake));

                    currentState = GameState::PLAYING;
                }
            }
        }
    }
}

void Game::Render()
{

    window.clear();
    if (currentState == GameState::MENU)
    {
        window.draw(titleText);
        window.draw(startButton);
        window.draw(startText);
    }
    else if (currentState == GameState::PLAYING)
    {
        window.draw(backgroundSprite);
        food.Draw(window);
        snake.draw(window);
        window.draw(scoreText);
        window.draw(fpsText);
    }
    else if (currentState == GameState::GAMEOVER)
    {
        window.draw(backgroundSprite);
        food.Draw(window);
        snake.draw(window);
        window.draw(scoreText);
        window.draw(gameOverText);
        window.draw(restartButton);
        window.draw(restartText);
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

