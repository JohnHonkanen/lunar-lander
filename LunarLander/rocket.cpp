#include "rocket.h"
#include <iostream>

Rocket::Rocket()
{

}

Rocket::Rocket(float x, float y, float f, float a, float ms)
{
	position = vector(x, y);
	velocity = vector(0, 0);
	fuel = f;
	acceleration = a;
	maxSpeed = ms;
	facingAngle = 0;
	accelerating = false;
}

Rocket::~Rocket()
{
}

void Rocket::controlEvent(unsigned char k, bool pressed)
{
	if (pressed)
	{
		switch (k)
		{
		case 'w':
			accelerating = true;
			break;
		case 'a':
			turningLeft = true;
			break;
		case 'd':
			turningRight = true;
		case 's':
			deacclerating = true;
		default:
			break;
		}
	}
	else
	{
		switch (k)
		{
		case 'w':
			accelerating = false;
			break;
		case 'a':
			turningLeft = false;
			break;
		case 'd':
			turningRight = false;
		case 's':
			deacclerating = false;
		default:
			break;
		}
	}
}

void Rocket::accelerate(vector accel)
{
	velocity.addTo(accel);
}

void Rocket::draw()
{
	glPointSize(0.1);
	const int NPOINTS = 3;
	const float TWOPI = 2 * 3.14159268;
	const float STEP = TWOPI / NPOINTS;
	glBegin(GL_POLYGON);
	for (float angle = 0; angle < TWOPI; angle += STEP)
		glVertex2f(50 * cos(angle + facingAngle + M_PI/2) + position.getX(), 50 * sin(angle + facingAngle + M_PI/2) + position.getY());
	glEnd();
}

void Rocket::update()
{
	if (turningLeft) {
		facingAngle += 0.05;
	}

	if (turningRight) {
		facingAngle -= 0.05;
	}

	thrust.setAngle(-facingAngle);

	if (accelerating)
	{
		thrust.setLength(acceleration);
	}
	else if (deacclerating)
	{
			thrust.setLength(-acceleration/2);
	}
	else
	{
		thrust.setLength(0);
	}


	accelerate(thrust);
	position.addTo(velocity);
}