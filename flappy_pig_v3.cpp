#include <SFML/Graphics.hpp>
using namespace sf;

int y=200;//current y cordinate of pig
int x=100;//x coordinate(only used for adjustment)
int yrecord=200;//y cordinate of the pig when up was pressed (used for the equation)

int main(){
    /// sets the render window

    RenderWindow window(VideoMode(880, 1056), "The Game!");
    //sets up textures
    Texture t1,t2;
    t1.loadFromFile("images/image_files/Background_small.png");
    t2.loadFromFile("images/image_files/Pig.png");
//sets up sprites
    Sprite Background;
    Background.setTexture(t1);

    Sprite Pig;
    Pig.setTexture(t2);
//scales things to make them bigger
    Pig.scale(4,4);
    Background.scale(4,4);

/////clock
    float timer=0,timer2=0.5,delay=0.016; 
    //timer is used for the refresh rate of the screen
    //timer2 is used to find the time since up was pressed (used in the equation)

    Clock clock;
//sets up the timer and timers
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        timer2+=time;
    

//////inputs
    float repressDelay=0.01;
        Event screen;
        while (window.pollEvent(screen))
        {
                if (screen.type == Event::Closed)
                    window.close(); //closes window
                if (timer2>repressDelay){ //checks when up was last pressed(used so you dont double jump)
                    if (screen.key.code==Keyboard::Up){ //up input
                        timer2=0;//resets timer2
                        yrecord=y; //record y cordinate when up was pressed
                    }
                }


        }

    ///////Tick
    if (timer>delay)//decides if screen needs to be refreshed
      {
        if (y<752){//checks if pig has hit the ground
        y=yrecord-((-200)*(timer2*timer2)+(200*timer2));//uses an parabola to calculate where the pig should be
        }
        else{ //if the pig has hit the ground
        y=752;//makes pig not in the ground
        }
      }


    /////////draw
        window.clear(Color::White);    
        window.draw(Background);
    ///pig settings
        Pig.setTextureRect(IntRect(0,0,30,30));//sets where the image starts and size
        Pig.setPosition(x,y);//sets location of pig
        window.draw(Pig);
        ///  display initiation
        window.display();
    }

    return 0;
}
//g++ -c flappy_pig_v2.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include
//g++ flappy_pig_v2.o -o sfml-app -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system