 #include <SFML/Graphics.hpp>

 int main()
 {
     sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800, 600}), "Snake Game");
     window.setFramerateLimit(60);

     sf::RectangleShape snakeHead(sf::Vector2f(20, 20));
     snakeHead.setOrigin(10, 10);
     snakeHead.setPosition(100, 100);
     snakeHead.setFillColor(sf::Color::Green);

     while (window.isOpen())
     {
         sf::Event event;
         while (window.pollEvent(event))
         {
             if (event.type == sf::Event::Closed)
             {
                 window.close();
             }
         }

        window.clear();
        window.draw(snakeHead);
         window.display();
     }
 }
