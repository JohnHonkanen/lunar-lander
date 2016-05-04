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
	radius = 25;
	colRadius = 15;
	locked = true;
}

Rocket::~Rocket()
{
}
//Keyboard Event
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
			break;
		case 'e':
			if (!dampeners)
			{
				dampeners = true;
			}
			else
			{
				dampeners = false;
			}
		case ' ':
			shot = true;
			break;
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
//Drawing our Rocket and Flame Thrusters
void Rocket::draw()
{
	float flameRad = 20;
	glPointSize(5);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex2f(radius * cos(M_PI * 0.5 + facingAngle) + position.getX(), radius * sin(M_PI * 0.5 + facingAngle) + position.getY());
	glVertex2f(radius * cos(M_PI * 1.75 + facingAngle) + position.getX(), radius * sin(M_PI * 1.75 + facingAngle) + position.getY());
	glVertex2f(position.getX(), position.getY());
	glVertex2f(radius * cos(M_PI * 1.25 + facingAngle) + position.getX(), radius * sin(M_PI * 1.25 + facingAngle) + position.getY());
	glEnd();
	if (accelerating && !locked)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex2f(flameRad * cos(M_PI * 1.5 + facingAngle) + position.getX(), flameRad * sin(M_PI * 1.5 + facingAngle) + position.getY());
		glVertex2f(1.3 * flameRad * cos(M_PI * 1.5 + facingAngle) + position.getX(), 1.3 * flameRad * sin(M_PI * 1.5 + facingAngle) + position.getY());
		glEnd();
	}
}

//Pointing our Arrow Indicator the particle


void Rocket::accelerate(vector accel)
{
	velocity.addTo(accel);
}
//Updating our Rocket's Velocity Via Input from Control Event
void Rocket::updateVelocity()
{
	if (turningLeft) {
		facingAngle += 0.05;
	}

	if (turningRight) {
		facingAngle -= 0.05;
	}

	thrust.setAngle(-facingAngle);

	if (fuel > 0)
	{
		if (accelerating)
		{
			fuel -= 0.1;
			thrust.setLength(acceleration);
		}
		else if (deacclerating)
		{
			fuel -= 0.1;
			thrust.setLength(-acceleration);

		}
		else
		{
			thrust.setLength(0);
			//Dampeners System
			if (dampeners)
			{
				fuel -= 0.5;
				if (velocity.getLength() < 2)
					velocity.setLength(0);
				else
					velocity.setLength(velocity.getLength() - acceleration);
			}
		}

	}
	else
	{
		thrust.setLength(0);
	}
	accelerate(thrust);
}
//Update our Position
void Rocket::updatePosition()
{
	position.addTo(velocity);
}
//Update Position based on Velocity
void Rocket::update()
{
	if (shot)
	{
		setLock(false);
	}

	if (crashed)
	{
		setLock(true);
	}

	if (landed)
	{
		setLock(true);
	}
	if (!locked)
	{
		updateVelocity();
		updatePosition();
	}
}
//Update Our Check for Collision
void Rocket::update(particle p, bool isTarget)
{
	collision(p, facingAngle, isTarget);
}

void Rocket::follow(tank t)
{
	position.setX((60) * cos(t.getInverseCannonAngle()) + t.cannonPosition.getX());
	position.setY((60) * sin(t.getInverseCannonAngle()) + t.cannonPosition.getY());
	setFacingAngle(t.getInverseCannonAngle() - (M_PI / 2));
}

float Rocket::getFuel()
{
	return fuel;
}

void Rocket::setFuel(float f)
{
	fuel = f;
}

float Rocket::getVelocity()
{
	return velocity.getLength();
}

float Rocket::getVelocityAngle()
{
	return velocity.getAngle();
}

bool Rocket::checkDampeners()
{
	return dampeners;
}

bool Rocket::checkCrashed()
{
	return crashed;
}
bool Rocket::checkLanded()
{
	return landed;
}

void Rocket::setFacingAngle(float angle) 
{

	facingAngle = angle;
}