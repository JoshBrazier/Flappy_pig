#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int y=200;//current y cordinate of pig
int x=100;//x coordinate(only used for adjustment)
int yrecord=200;//y cordinate of the pig when up was pressed (used for the equation)
float a;// x coordinate of the mouse when you click 
float b; // y coordinate of the mouse when it is clicked
int c =0;// tells the program to look at the mouse click when it is 1
int Screennumber=1; // screen number 1 is home screen screen number 2 is playing screen
int start = 0; // used to determine if the play has clicked pressed up and the pig will start flying
int died = 0; //turs to 1 when the pig dies
int score = 0; // used to count the score
int recentscore = 0;
int highscore = 0;

////pipe stuff
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

    RenderWindow window(VideoMode(880, 1056), "The Game!");
    //sets up textures
    Texture t1,t2,t3,t4,t5,t6;
    t1.loadFromFile("images/image_files/Background_small.png");
    t2.loadFromFile("images/image_files/Pig.png");
    t3.loadFromFile("images/image_files/Numbers.png");
    t4.loadFromFile("images/image_files/Startup.png");
    t5.loadFromFile("images/image_files/Pipe.png");
    t6.loadFromFile("images/image_files/Base_plate.png");
//sets up sprites
    Sprite Background;
    Background.setTexture(t1);
    int number=0;/// the number that will be displayed while playing the game in the ones column
    int number2=0;/// the number in the tens column

///// load sprite textures
    Sprite Numbers;
    Numbers.setTexture(t3);

    Sprite Numbers2;
    Numbers2.setTexture(t3);

    Sprite Pig;
    Pig.setTexture(t2);

    Sprite Home;
    Home.setTexture(t4);

        Sprite Pipe1;
    Pipe1.setTexture(t5);

    Sprite Pipe2;
    Pipe2.setTexture(t5);

    Sprite Pipe3;
    Pipe3.setTexture(t5);

    Sprite Pipe4;
    Pipe4.setTexture(t5);

    Sprite Base;
    Base.setTexture(t6);

//scales sprites to fit the screen
    Pig.scale(4,4);
    Background.scale(4,4);
    Numbers.scale(8,8);
    Numbers2.scale(8,8);
    Home.scale(4,4);
        Pipe1.scale(4,4);
    Pipe2.scale(4,4);
    Pipe3.scale(4,4);
    Pipe3.rotate(180);
    Pipe4.scale(4,4);
    Pipe4.rotate(180);
    Base.scale(4,4);

/////clock
    float timer=0,timer2=0.5,timer3=0,timer4=0,timer5=0,delay=0.016,pipe_timer=0; 
    //timer is used for the refresh rate of the screen
    //timer2 is used to find the time since up was pressed (used in the equation)

    Clock clock;
//sets up the timer and timers
    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        //set up timers
        timer+=time;
        timer2+=time;
        if (died==1){
        timer3+=time;
        }
        timer4+=time;
        timer5+=time;

        pipe_timer+=time;

    /// timer for the ones column of the score
    if (Screennumber==2){
    if (score==1){
        recentscore+=1;
        if(number == 9){
            number = 0;
            number2+=1;
        }
        else{number+=1;}
        score = 0;
    }
    }

//////inputs
    float repressDelay=0.15;

        Event screen;
        while (window.pollEvent(screen))
        {
                if (screen.type == Event::Closed){
                    window.close(); //closes window
                }
            if (Screennumber==2){
                if (timer2>repressDelay){ //checks when up was last pressed(used so you dont double jump)
                    if (screen.key.code==Keyboard::Up){ //up input
                        timer2=0;//resets timer2
                        if (start==0){//determines if this is the first jump
                            start=1;
                            yrecord=200;
                        }
                        yrecord=y; //record y cordinate when up was pressed
                    }
                }
            }

        }
        if (Screennumber==1){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        a = sf::Mouse::getPosition(window).x;
        b = sf::Mouse::getPosition(window).y;
        c=1;// c is used to tell the code that the mouse has been clicked and it needs to look as the coordinates
        }
        }
    ///////Tick
    if (Screennumber==2 && died==0){
    if (timer>delay)//decides if screen needs to be refreshed
      {
        if (y<752 && start==1){//checks if pig has hit the ground
        y=yrecord-((-1200)*(timer2*timer2)+(600*timer2));//uses an parabola to calculate where the pig should be
        }
        else if(y>=752 && start==1 && died ==0){ //if the pig has hit the ground and is in play
        y=752;//makes pig not in the ground
        timer4=0;
        died = 1;

        }
      }
    }

       // collision of pipes
        if (pipe_x1 > 10 && pipe_x1 < 200 && (y > pipe_y1 - 80 || y < pipe_y3 - 20)) {
            if(died == 0){
        died=1;
        timer4 = 0;
            }
    }
        if (pipe_x2 > 10 && pipe_x2 < 200 && (y > pipe_y2 - 80 || y < pipe_y4 - 20)) {
            if(died == 0){
        died=1;
        timer4=0;
            }
    }

    // counting score
        if ((pipe_x1 == 10 || pipe_x2 == 10) && timer5 > 0.1) {
            score = 1;
            timer5 = 0;
        } 


    ///setting the wait period for once the player dies
    if (timer4>1 && died ==1){
        //game reset
        Screennumber=1;
        start = 0;
        died = 0;
        number = 0;
        number2=0;
        yrecord=200;
        y=200;
//pipe reset
        pipe_x1=880;
        pipe_y1=678;
        pipe1_count = 0;

        pipe_x2=1400;
        pipe_y2=678;
        pipe2_count = 0;

        pipe_x3=1040;
        pipe_y3=378;

        pipe_x4=1560;
        pipe_y4=378;


            if (recentscore>highscore){
                highscore=recentscore;
            }
    }

        // Pipe 1 Scroller
    if (pipe_timer > 0.005 && start==1 && died == 0) {
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

        if (Screennumber==2){  
        window.draw(Background);
    ///pig settings
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

    //// number settings
    //for 0 to 9
        Numbers.setTextureRect(IntRect(number*8,0,8,12));
        Numbers.setPosition(408,100);
    //for 10-99
    if(number2>0){
        Numbers2.setTextureRect(IntRect(number2*8,0,8,12));
        Numbers.move(32,0);
        Numbers2.setPosition(370,100);
        window.draw(Numbers2);
        }
        window.draw(Numbers);

        }
        if (Screennumber == 1){
            window.draw(Home);

            if (b>400 && c==1 && b<600 && a>190 && a<680){
            Screennumber=2;
            c=0;
            timer2=0;
        }
        }
        window.display();
    }

    return 0;
}
//g++ -c flappy_pig_v3.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include
//g++ flappy_pig_v3.o -o sfml-app -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system