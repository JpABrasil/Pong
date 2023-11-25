#include "Bat.h"

// This the constructor and it is called when we create an object
Bat::Bat(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;
	
	m_Shape.setSize(sf::Vector2f(50, 5));
	m_Shape.setPosition(m_Position);
}

FloatRect Bat::getPosition()
{
	return m_Shape.getGlobalBounds();
}

RectangleShape Bat::getShape() //Just returns a copy of m_shape to the calling code so we can draw the bat in the mais function
{
	return m_Shape;
}

void Bat::moveLeft()	//To keep track of the player intention
{
	m_MovingLeft = true;
}

void Bat::moveRight()
{
	m_MovingRight = true;
}

void Bat::stopLeft()
{
	m_MovingLeft = false;
}

void Bat::stopRight()
{
	m_MovingRight = false;
}

void Bat::update(Time dt)	//Call this function one per frame, Having an update in bat class rather than in main is encapsulation, each object will be responsible for updating themselves
{
	if (m_MovingLeft)
	{
		m_Position.x -= m_speed * dt.asSeconds();//dt = delta time
	}
	if (m_MovingRight)
	{
		m_Position.x += m_speed * dt.asSeconds();
	}

	m_Shape.setPosition(m_Position);
}



