 #include <SFML/Graphics.hpp>

 int main()
 {
     auto window = sf::RenderWindow(sf::VideoMode({800, 600}), "Snake Game");
     window.setFramerateLimit(60);



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
         window.display();
     }
 }
