#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 504), "SFML works!");
    sf::CircleShape shape(50.f);
    shape.setPosition(400,100);
    shape.setFillColor(sf::Color::Blue);

    sf::Texture texture;
    if (!texture.loadFromFile("assets/background.png")) {
    std::cout << "Could not load enemy texture" << std::endl;
    return 0;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(texture);

    sf::Clock clock;
    
    float timer=1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space){
                    shape.move(0.0f,-10.0f);
                }
            }

            if (clock.getElapsedTime().asSeconds() > 1) {
                shape.move(0.0f,1.0f);
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(shape);
        window.display();
    }

    return 0;
}