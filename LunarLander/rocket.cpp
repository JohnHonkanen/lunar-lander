#include "rocket.h"

Rocket::Rocket()
{

}
/*
	Constructor
	@param x	X coordinate
	@param y	Y cooridinate
	@param f	Fuel
	@param a	Acceleration Speed
	@param ms	Max Speed
*/
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
/*
	Keyboard Control Event
	@param k	Key that was pressed
	@param pressed	Keydown(true) or KeyUp(false)	
*/
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
/*
	Draw our Rocket and Thrusters
*/
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

/*
	Accelerate our Particle towards a Direction using Vector
	@param accel	Vector with Magnitude and Angle
*/
void Rocket::accelerate(vector accel)
{
	velocity.addTo(accel);
}
/*
	Update Velocity Magnitude and Angle Based on Controls
*/
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
/*
	Update Our Position on Screen
*/
void Rocket::updatePosition()
{
	position.addTo(velocity);
}
/*
	Run Update Functions and Set Locks and Win condition
*/
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
/*
	Checks Collision with a particle
	@param p	Particle
	@param isTarget	if Win Condition
*/
void Rocket::update(particle p, bool isTarget)
{
	collision(p, facingAngle, isTarget);
}

/*
	Attach our Rocket to Tank
	@param t	Tank to attach to
*/
void Rocket::follow(tank t)
{
	position.setX((60) * cos(t.getInverseCannonAngle()) + t.cannonPosition.getX());
	position.setY((60) * sin(t.getInverseCannonAngle()) + t.cannonPosition.getY());
	setFacingAngle(t.getInverseCannonAngle() - (M_PI / 2));
}

/*
	Get Fuel Value
	@return Fuel Value
*/
float Rocket::getFuel()
{
	return fuel;
}

/*
	Set Fuel Value
	@param f Fuel Value
*/
void Rocket::setFuel(float f)
{
	fuel = f;
}
/*
	Get Velocity Length/Magnitude/Speed
	@return Magnitude
*/
float Rocket::getVelocity()
{
	return velocity.getLength();
}
/*
	Get Velocity Angle
	@return Angle
*/
float Rocket::getVelocityAngle()
{
	return velocity.getAngle();
}
/*
	Check Dampeners on or off
	@return True or False
*/
bool Rocket::checkDampeners()
{
	return dampeners;
}
/*
	Check Crash Value
	@return True or False
*/
bool Rocket::checkCrashed()
{
	return crashed;
}
/*
	Check Landed Value
	@return True or False
*/
bool Rocket::checkLanded()
{
	return landed;
}
/*
	Set Facing Angle of Rocket
	@param angle	Angle in Radians
*/
void Rocket::setFacingAngle(float angle) 
{

	facingAngle = angle;
}