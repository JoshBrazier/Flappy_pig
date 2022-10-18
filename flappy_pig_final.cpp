#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace sf;
using namespace std;

int *ptr_y = new int; // initialising dynamic integer for y location of pig
int x = 100;  // x coordinate of pig (only used for adjustment)
int yrecord = 200;  // y cordinate of the pig when up was pressed (used for the equation)
float a;  // x coordinate of the mouse when you click
float b;  // y coordinate of the mouse when you click
int c = 0;  // boolean click toggle for if mouse is clicked or not
int Screennumber = 1;  // screen number 1 is home screen screen number 2 is playing screen
int start = 0;  // used to determine if the play has clicked pressed up and the pig will start flying
int died = 0;   // boolean which turns to 1 when the pig dies
int score = 0;  // used to count the current score
int recentscore = 0; // calculates the recent high score whilst in game
float highscore = 0; // calculates true high score to be displayed
int number = 0;  // the number that will be displayed while playing the game in the ones column
int number2 = 0;  // the number in the tens column
int recentnumber = 0; // most recent score just made in the ones column
int recentnumber2 = 0; // most recent score just made in the tens column
int highnumber = 0; // high score in the ones column
int highnumber2 = 0; // high score in the tens column

// pipe initialised coordinates
int pipe_x1 = 880;
int pipe_y1 = 678;
int pipe1_count = 0;

int pipe_x2 = 1400;
int pipe_y2 = 678;
int pipe2_count = 0;

int pipe_x3 = 1040;
int pipe_y3 = 378;

int pipe_x4 = 1560;
int pipe_y4 = 378;

int main() {
  *ptr_y = 200; // initialise dynamic integer for pigs location

  // opening the save file which contains the high global high score
  ifstream myfile;
  myfile.open("data.txt");
  myfile >> highscore;
  cout << highscore;
  myfile.close();
  highnumber2 = floor(highscore / 10);
  highnumber = highscore - (highnumber2 * 10);

  // sets the render window in which the game will be displayed
  RenderWindow window(VideoMode(880, 1056), "Flappy Pig!!!");

  // Initialising and loading all images from files
  Texture t1, t2, t3, t4, t5, t6, t7;
  t1.loadFromFile("images/image_files/Background_small.png");
  t2.loadFromFile("images/image_files/Pig.png");
  t3.loadFromFile("images/image_files/Numbers.png");
  t4.loadFromFile("images/image_files/Startup.png");
  t5.loadFromFile("images/image_files/Pipe.png");
  t6.loadFromFile("images/image_files/Base_plate.png");
  t7.loadFromFile("images/image_files/Gold_pig.png");

  // Creating entities from the image files
  Sprite Background;
  Background.setTexture(t1);

  // Gold pig texture for when player surpasses high score
  Sprite Gold;
  Gold.setTexture(t7);

  // score shown while playing
  Sprite Numbers;
  Numbers.setTexture(t3);

  Sprite Numbers2;
  Numbers2.setTexture(t3);

  // recent score on home screen
  Sprite recentNumber;
  recentNumber.setTexture(t3);

  Sprite recentNumbers2;
  recentNumbers2.setTexture(t3);

  // recent high score on home screen
  Sprite highNumber;
  highNumber.setTexture(t3);

  Sprite highNumbers2;
  highNumbers2.setTexture(t3);

  // game sprites
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

  // scales and rotates sprites to fit the screen
  Pig.scale(4, 4);
  Gold.scale(4, 4);
  Background.scale(4, 4);
  Numbers.scale(8, 8);
  Numbers2.scale(8, 8);
  recentNumber.scale(4, 4);
  recentNumbers2.scale(4, 4);
  highNumber.scale(4, 4);
  highNumbers2.scale(4, 4);
  Home.scale(4, 4);
  Pipe1.scale(4, 4);
  Pipe2.scale(4, 4);
  Pipe3.scale(4, 4);
  Pipe3.rotate(180);
  Pipe4.scale(4, 4);
  Pipe4.rotate(180);
  Base.scale(4, 4);

  // initialising clock variables which create a tick
  float timer = 0, timer2 = 0.5, timer3 = 0, timer4 = 0, timer5 = 0,
        delay = 0.016, pipe_timer = 0;

  // timer is used for the refresh rate of the screen
  // timer2 is used to find the time since up was pressed (used in the equation)
  // timer3 is used to calculate the home screen uptime
  // timer4 is used to create a delay between dying and the home screen being shown
  // timer5 is used to control the scoring
  // delay is used to control the speed of the game
  // pipe_timer is used to control the speed of the pipes

  Clock clock; // sets up the timer and timers

  while (window.isOpen()) {
    float time = clock.getElapsedTime().asSeconds();
    clock.restart(); // getting the elapsed time since last clock refresh

    // adding the elapsed time to each of the timers
    timer += time;
    timer2 += time;
    if (died == 1) {
      timer3 += time;
    }
    timer4 += time;
    timer5 += time;
    pipe_timer += time; 

    // displaying score at the top of the screen
    if (Screennumber == 2) {
      if (score == 1) {
        recentscore += 1;
        if (number == 9) {
          number = 0;
          number2 += 1;
        } else {
          number += 1;
        }
        score = 0;
      }
    }

    float repressDelay = 0.15; // input delay number to prevent accidental double clicks

    Event screen;
    while (window.pollEvent(screen)) {
      if (screen.type == Event::Closed) {
        window.close();  // closes window when exited
      }
      
      // jumping mechanism
      if (Screennumber == 2) {
        if (timer2 > repressDelay) {  // checks when up was last pressed so you dont double jump
          if (screen.key.code == Keyboard::Up) {  // up input
            timer2 = 0; // resets timer2 when up pressed
            if (start == 0) {  // determines if this is the first jump
              start = 1;
              yrecord = 200;
            }
            yrecord = *ptr_y;  // records y coordinate when up was pressed
          }
        }
      }
    }

    // entering from the start screen to the game
    if (Screennumber == 1) {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        a = sf::Mouse::getPosition(window).x;
        b = sf::Mouse::getPosition(window).y;
        c = 1;  // c is used to tell the code that the mouse has been clicked
                // and it needs to look as the coordinates of the click
      }
    }

    // gravity simulation on pig
    if (Screennumber == 2 && died == 0) {
      if (timer > delay)  // decides if screen needs to be refreshed
      {
        if (*ptr_y < 752 && start == 1) {  // checks if pig has hit the ground
          *ptr_y = yrecord - ((-1200) * (timer2 * timer2) +
                              (600 * timer2));  // uses an parabola to calculate
                                                // where the pig should be
        } else if (*ptr_y >= 752 && start == 1 &&
                   died == 0) {  // if the pig has hit the ground and is in play
          *ptr_y = 752;          // makes pig not in the ground
          timer4 = 0;
          died = 1;
        }
      }
    }

    // collision of pipes
    if (pipe_x1 > 10 && pipe_x1 < 200 &&
        (*ptr_y > pipe_y1 - 80 || *ptr_y < pipe_y3 - 20)) { // checking pig coordinates aren't the same as pipe coordinates
      if (died == 0) {
        died = 1; // kill pig if coordinates match
        timer4 = 0; // resets timer
      }
    }
    if (pipe_x2 > 10 && pipe_x2 < 200 &&
        (*ptr_y > pipe_y2 - 80 || *ptr_y < pipe_y4 - 20)) { // checking pig coordinates aren't the same as pipe coordinates
      if (died == 0) {
        died = 1; // kill pig if coordinates match
        timer4 = 0; // resets timer
      }
    }

    // counting score
    if ((pipe_x1 == 10 || pipe_x2 == 10) && timer5 > 0.1) {
      score = 1;
      timer5 = 0;
    }

    /// setting the wait period for once the player dies
    if (timer4 > 1 && died == 1) {
      recentnumber = number;  // coppies the score of that round to be displayed on home screen
      recentnumber2 = number2;
      // enters high score into 'data.txt' file
      if (recentscore > highscore) {
        highscore = recentscore;
        highnumber = recentnumber;
        highnumber2 = recentnumber2;
        ofstream file;
        file.open("data.txt", std::ofstream::out | std::ofstream::trunc);
        file.close();
        ofstream myfile;
        myfile.open("data.txt", std::ios::app);
        myfile << highscore << " " << endl;
        myfile.close();
      }
      
      // resets all variables to original state when dead
      recentscore = 0;
      Screennumber = 1;
      start = 0;
      died = 0;
      number = 0;
      number2 = 0;
      yrecord = 200;
      *ptr_y = 200;

      pipe_x1 = 880;
      pipe_y1 = 678;
      pipe1_count = 0;

      pipe_x2 = 1400;
      pipe_y2 = 678;
      pipe2_count = 0;

      pipe_x3 = 1040;
      pipe_y3 = 378;

      pipe_x4 = 1560;
      pipe_y4 = 378;
    }

    // Pipe scroller
    if (pipe_timer > 0.005 && start == 1 && died == 0) {
      pipe_x1 -= 2; // moves pipes 2 pixels every 0.005 seconds
      pipe_x2 -= 2; // moves pipes 2 pixels every 0.005 seconds
      pipe_x3 -= 2; // moves pipes 2 pixels every 0.005 seconds
      pipe_x4 -= 2; // moves pipes 2 pixels every 0.005 seconds
      pipe_timer = 0; // resets the pipe timer
      if (pipe_x1 < -160) {
        pipe_x1 = 880; // resets pipe when off the screen
        pipe_x3 = 1040; // resets pipe when off the screen
        pipe_y3 = rand() % 400 + 100; // takes a random number which randomly generates the pipes height
        pipe_y1 = pipe_y3 + 300; // creates a consistent gap between bottom and top pipe
      }
      if (pipe_x2 < -160) {
        pipe_x2 = 880; // resets pipe when off the screen
        pipe_x4 = 1040; // resets pipe when off the screen
        pipe_y4 = rand() % 400 + 100; // takes a random number which randomly generates the pipes height
        pipe_y2 = pipe_y4 + 300; // creates a consistent gap between bottom and top pipe
      }
    }

    // drawing all entities
    window.clear(Color::White);

    if (Screennumber == 2) {
      window.draw(Background);

      // pig settings
      if (recentscore <= highscore) { // checks if user has surpassed high score
        Pig.setTextureRect(
            IntRect(0, 0, 30, 30)); // sets where the image starts and size
        Pig.setPosition(x, *ptr_y); // sets location of pig
        window.draw(Pig);
      } else { // for when the user has surpassed high score
        Gold.setTextureRect(IntRect(0, 0, 30, 30)); // sets where the image starts and size
        Gold.setPosition(x, *ptr_y); // sets location of pig
        window.draw(Gold);
      }

      // Pipe 1 Settings
      Pipe1.setPosition(pipe_x1, pipe_y1); // sets location of pipe
      window.draw(Pipe1);
      // Pipe 2 Settings
      Pipe2.setPosition(pipe_x2, pipe_y2); // sets location of pipe
      window.draw(Pipe2);
      // Pipe 3 Settings
      Pipe3.setPosition(pipe_x3, pipe_y3); // sets location of pipe
      window.draw(Pipe3);
      // Pipe 4 Settings
      Pipe4.setPosition(pipe_x4, pipe_y4); // sets location of pipe
      window.draw(Pipe4);

      // Base settings which overlap the pipes on the ground
      Base.setPosition(0, 864);
      window.draw(Base);

      // number settings for 0 to 9
      Numbers.setTextureRect(IntRect(number * 8, 0, 8, 12));
      Numbers.setPosition(408, 100);

      // for 10-99
      if (number2 > 0) {
        Numbers2.setTextureRect(IntRect(number2 * 8, 0, 8, 12));
        Numbers.move(32, 0);
        Numbers2.setPosition(370, 100);
        window.draw(Numbers2);
      }
      window.draw(Numbers);
    }

    // drawing home screen including all score values
    if (Screennumber == 1) {
      window.draw(Home);
      // printing out high scores
      recentNumber.setTextureRect(IntRect(recentnumber * 8, 0, 8, 12));
      recentNumber.setPosition(550, 264);
      recentNumbers2.setTextureRect(IntRect(recentnumber2 * 8, 0, 8, 12));
      recentNumbers2.setPosition(520, 264);
      highNumber.setTextureRect(IntRect(highnumber * 8, 0, 8, 12));
      highNumber.setPosition(550, 340);
      highNumbers2.setTextureRect(IntRect(highnumber2 * 8, 0, 8, 12));
      highNumbers2.setPosition(520, 340);

      // drawing the numbers
      window.draw(recentNumber);
      if (recentnumber2 > 0) {
        window.draw(recentNumbers2);
      }
      window.draw(highNumber);
      if (highnumber2 > 0) {
        window.draw(highNumbers2);
      }

      // checking if user wants to start the game
      if (b > 400 && c == 1 && b < 600 && a > 190 && a < 680) {
        Screennumber = 2;
        c = 0;
        timer2 = 0;
      }
    }
    window.display();
  }

  delete ptr_y; // releasing the y coordinate from dynamic memory when the game is closed
  return 0;
}

/* compiler commands */

// g++ -c flappy_pig_v3.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include
// g++ flappy_pig_v3.o -o sfml-app -L/usr/local/Cellar/sfml/2.5.1_2/lib
// -lsfml-graphics -lsfml-window -lsfml-system