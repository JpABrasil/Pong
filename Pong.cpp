#include <sstream>
#include "Bat.h"
#include "Ball.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	//Create a videoMode object
	VideoMode vm(1920, 1080);

	//Create and open a window for the game
	RenderWindow window(vm, "Pong by Jp", Style::Fullscreen);

	int score = 0;
	int lives = 3;

	//Create a bat at the bottom center of the screen
	Bat bat(1920 / 2, 1080 - 20);

	//Add a Ball
	Ball ball(1920 / 2, 1080/2);

	//Create a Text object called HUD
	Text hud;

	//Font
	Font font;
	font.loadFromFile("fonts/DS-DIGI.ttf");

	//Set the font to the text, changing size, choosing a color and setting the position
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);

	//Our clock for timing everything
	Clock clock;

	while (window.isOpen())
	{
		/*
		* Handle the player input
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				//Quit the game when clicked to close
				window.close();
			}
		}

		//Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//Handle player pressing and releasing arrow keys
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			bat.moveLeft();
		}													//If the key is pressed the bat move, when stop to be pressed the bat stopos
		else
		{
			bat.stopLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			bat.moveRight();
		}													//If the key is pressed the bat move, when stop to be pressed the bat stopos
		else
		{
			bat.stopRight();
		}


		/*
		*Update the bat, the ball and the HUD
		*/
		//Update the delta time
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);
		
		//Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << " Lives:" << lives;
		hud.setString(ss.str());

		//Handle the ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			//reverse ball direction
			ball.reboundBottom();//This function was defined in Ball.cpp

			//Remove a life
			lives--;

			//Check for zero lifes
			if (lives <= -1)
			{
				//Reset the score
				score = 0;
				//Reset the lives
				lives = 3;
			}

		}

		//Handle the ball hitting the top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatorTop();

			//Add a point to the players score
			score++;
		}

		//Handle the ball hitting the sides
		if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x)
		{
			ball.reboundSides();
		}


		//Handle the ball hitting the bate
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			//Hit detected so reverse the ball and score a point
			ball.reboundBatorTop();
		}

		/*
		* Draw the ball, the bat and the HUD
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape()); //Grabs the RectangleShape instance from the Bat instance and draw it to the screen
		window.draw(ball.getShape());
		window.display();
	}


	return 0;
}
