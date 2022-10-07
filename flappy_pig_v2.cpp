#include <SFML/Graphics.hpp>
using namespace sf;

int y=200;

int main(){
        srand(time(0));  

    RenderWindow window(VideoMode(880, 1056), "The Game!");

    Texture t1,t2;
    t1.loadFromFile("images/image_files/Background_small.png");
    t2.loadFromFile("images/image_files/Pig.png");

    Sprite Background;
    Background.setTexture(t1);

    Sprite Pig;
    Pig.setTexture(t2);

    Pig.scale(4,4);
    Background.scale(4,4);

/////clock
    float timer=0,delay=0.001; 

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

//////i think this does something when everything else is doing nothing
        Event screen;
        while (window.pollEvent(screen))
        {
                if (screen.type == Event::Closed)
                    window.close();
        }

    ///////Tick
    if (timer>delay)
      {
        if (y<752){
        y+=1; 
        timer=0;
        }
        else{timer = 0;}
      }


    /////////draw
        window.clear(Color::White);    
        window.draw(Background);
    ///pig settings
        Pig.setTextureRect(IntRect(0,0,30,30));
        Pig.setPosition(0,y);
        Pig.move(200,0);
        window.draw(Pig);
        ///  display initiation
        window.display();
    }

    return 0;
}
//g++ -c flappy_pig_v1.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include
//g++ flappy_pig_v1.o -o sfml-app -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system