#include <SFML/Graphics.hpp>
using namespace sf;

int main(){
    RenderWindow window(VideoMode(880, 1056), "The Game!");

    Texture t1,t2;
    t1.loadFromFile("images/image_files/Background_small.png");
    //t2.loadFromFile("images/image_files/Pig.png");

    Sprite Background;
    Background.setTexture(t1);

    Background.scale(4,4);

   
    while (window.isOpen()){
        Event event;
     while(window.pollEvent(event))
     {

     if (event.type==Event::Closed)
        window.close();
     }
    
    window.clear(Color::White);    
    window.draw(Background);
    window.display();
    }
    return 0;
}
//g++ -c flappy_pig_v1.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include
//g++ flappy_pig_v1.o -o sfml-app -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system