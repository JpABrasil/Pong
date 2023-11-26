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

	int score_player_1 = 0;
	int score_player_2 = 0;

	//Create a bat at the bottom center of the screen
	Bat bat1(1920 / 2, 1080 - 20);
	Bat bat2(1920 / 2, 20);
	//Add a Ball
	Ball ball(1920 / 2, 1080/2);

	//Create a Text object called HUD
	Text hud1;
	Text hud2;
	//Font
	Font font;
	font.loadFromFile("fonts/DS-DIGI.ttf");

	//Set the font to the text, changing size, choosing a color and setting the position
	hud1.setFont(font);
	hud1.setCharacterSize(45);
	hud1.setFillColor(Color::White);
	hud1.setPosition(20, 20);
	hud2.setFont(font);
	hud2.setCharacterSize(45);
	hud2.setFillColor(Color::White);
	hud2.setPosition(20, 1000);
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

		//Handle player1 pressing and releasing arrow keys
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			bat1.moveLeft();
		}													//If the key is pressed the bat move, when stop to be pressed the bat stopos
		else
		{
			bat1.stopLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			bat1.moveRight();
		}													//If the key is pressed the bat move, when stop to be pressed the bat stopos
		else
		{
			bat1.stopRight();
		}

		//Handle player2 pressing and releasing arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat2.moveLeft();
		}													//If the key is pressed the bat move, when stop to be pressed the bat stopos
		else
		{
			bat2.stopLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat2.moveRight();
		}													//If the key is pressed the bat move, when stop to be pressed the bat stopos
		else
		{
			bat2.stopRight();
		}

		/*
		*Update the bat, the ball and the HUD
		*/
		//Update the delta time
		Time dt = clock.restart();
		bat1.update(dt);
		bat2.update(dt);
		ball.update(dt);
		
		//Update the HUD text
		std::stringstream ss1;
		ss1 << "Player 1:" << score_player_1;
		hud1.setString(ss1.str());
		std::stringstream ss2;
		ss2 << "Player 2:" << score_player_2;
		hud2.setString(ss2.str());


		//Handle the ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			//reverse ball direction
			ball.reboundBottom();//This function was defined in Ball.cpp

			//Add score to player 2
			score_player_2++;
		}

		//Handle the ball hitting the top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBottom();

			//Add a point to the players score
			score_player_1++;
		}

		//Handle the ball hitting the sides
		if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x)
		{
			ball.reboundSides();
		}


		//Handle the ball hitting the bat1
		if (ball.getPosition().intersects(bat1.getPosition()))
		{
			//Hit detected so reverse the ball and score a point
			ball.reboundBatorTop();
		}

		//Handle the ball hitting the bat2
		if (ball.getPosition().intersects(bat2.getPosition()))
		{
			//Hit detected so reverse the ball and score a point
			ball.reboundBatorTop();
		}

		/*
		* Draw the ball, the bat and the HUD
		*/
		window.clear();
		window.draw(hud1);
		window.draw(hud2);
		window.draw(bat1.getShape()); //Grabs the RectangleShape instance from the Bat instance and draw it to the screen
		window.draw(bat2.getShape());
		window.draw(ball.getShape());
		window.display();
	}


	return 0;
}
