#include <sstream>
#include "Bat.h"
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
		
		//Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << " Lives:" << lives;
		hud.setString(ss.str());




		/*
		* Draw the ball, the bat and the HUD
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape()); //Grabs the RectangleShape instance from the Bat instance and draw it to the screen
		window.display();
	}


	return 0;
}
