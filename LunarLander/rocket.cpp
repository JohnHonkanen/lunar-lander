#include "rocket.h"

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
			break;
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
			break;
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
	radius = 25;
	float flameRad = 20;
	glPointSize(5);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex2f(radius * cos(M_PI * 0.5 + facingAngle) + position.getX(), radius * sin(M_PI * 0.5 + facingAngle) + position.getY());
	glVertex2f(radius * cos(M_PI * 1.75 + facingAngle) + position.getX(), radius * sin(M_PI * 1.75 + facingAngle) + position.getY());
	glVertex2f(position.getX(), position.getY());
	glVertex2f(radius * cos(M_PI * 1.25 + facingAngle) + position.getX(), radius * sin(M_PI * 1.25 + facingAngle) + position.getY());
	glEnd();
	if (accelerating)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex2f(flameRad * cos(M_PI * 1.5 + facingAngle) + position.getX(), flameRad * sin(M_PI * 1.5 + facingAngle) + position.getY());
		glVertex2f(1.3 * flameRad * cos(M_PI * 1.5 + facingAngle) + position.getX(), 1.3 * flameRad * sin(M_PI * 1.5 + facingAngle) + position.getY());
		glEnd();
	}
}

void Rocket::updateVelocity()
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
}

void Rocket::updatePosition()
{
	position.addTo(velocity);
}