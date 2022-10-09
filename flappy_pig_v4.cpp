#include <SFML/Graphics.hpp>
using namespace sf;

int y=200;//current y cordinate of pig
int x=100;//x coordinate(only used for adjustment)
int yrecord=200;//y cordinate of the pig when up was pressed (used for the equation)

int pipe_x1=880;
int pipe_y1=678;
int pipe1_count = 0;

int pipe_x2=1400;
int pipe_y2=678;
int pipe2_count = 0;

int pipe_x3=1040;
int pipe_y3=378;

int pipe_x4=1560;
int pipe_y4=378;

int main(){
    /// sets the render window
    RenderWindow window(VideoMode(880, 1056), "The Game v4.0!");

    //sets up textures
    Texture t1,t2,t3,t4;
    t1.loadFromFile("images/image_files/Background_small.png");
    t2.loadFromFile("images/image_files/Pig.png");
    t3.loadFromFile("images/image_files/Pipe.png");
    t4.loadFromFile("images/image_files/Base_plate.png");

//sets up sprites
    Sprite Background;
    Background.setTexture(t1);

    Sprite Pig;
    Pig.setTexture(t2);

    Sprite Pipe1;
    Pipe1.setTexture(t3);

    Sprite Pipe2;
    Pipe2.setTexture(t3);

    Sprite Pipe3;
    Pipe3.setTexture(t3);

    Sprite Pipe4;
    Pipe4.setTexture(t3);

    Sprite Base;
    Base.setTexture(t4);

//scales things to make them bigger
    Pig.scale(4,4);
    Background.scale(4,4);
    Pipe1.scale(4,4);
    Pipe2.scale(4,4);
    Pipe3.scale(4,4);
    Pipe3.rotate(180);
    Pipe4.scale(4,4);
    Pipe4.rotate(180);
    Base.scale(4,4);

/////clock
    float timer=0,timer2=0.5,delay=0.016,pipe_timer=0;
    //timer is used for the refresh rate of the screen
    //timer2 is used to find the time since up was pressed (used in the equation)

    Clock clock;
//sets up the timer and timers
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        float pipe_time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        timer+=time;
        timer2+=time;
        pipe_timer+=time;

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
        y=yrecord-((-1000)*(timer2*timer2)+(600*timer2));//uses an parabola to calculate where the pig should be
        }
        else{ //if the pig has hit the ground
        y=752;//makes pig not in the ground
        }
      }

    // Pipe 1 Scroller
    if (pipe_timer > 0.005) {
        pipe_x1 -= 1;
        pipe_x2 -= 1;
        pipe_x3 -= 1;
        pipe_x4 -= 1;
        pipe_timer = 0;
        if (pipe_x1 < -160) {
            pipe_x1 = 880; 
            pipe_x3 = 1040;
            pipe_y3 = rand() % 400 + 100;
            pipe_y1 = pipe_y3 + 300;
        }
        if (pipe_x2 < -160) {
            pipe_x2 = 880;
            pipe_x4 = 1040;
            pipe_y4 = rand() % 400 + 100;
            pipe_y2 = pipe_y4 + 300;
        }
    }

    /////////draw
        window.clear(Color::White);    
        window.draw(Background);
    // Pig settings
        Pig.setTextureRect(IntRect(0,0,30,30));//sets where the image starts and size
        Pig.setPosition(x,y);//sets location of pig
        window.draw(Pig);
    // Pipe 1 Settings
        Pipe1.setPosition(pipe_x1,pipe_y1);
        window.draw(Pipe1);
    // Pipe 2 Settings
        Pipe2.setPosition(pipe_x2,pipe_y2);
        window.draw(Pipe2);
    // Pipe 3 Settings
        Pipe3.setPosition(pipe_x3,pipe_y3);
        window.draw(Pipe3);
    // Pipe 4 Settings
        Pipe4.setPosition(pipe_x4,pipe_y4);
        window.draw(Pipe4);
    // Base
        Base.setPosition(0,864);
        window.draw(Base);
    //  display initiation
        window.display();
    }

    return 0;
}
//g++ -c flappy_pig_v2.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include
//g++ flappy_pig_v2.o -o sfml-app -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system