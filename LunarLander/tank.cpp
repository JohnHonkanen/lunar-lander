#include "tank.h"

/*
	Constructor
	@param pos - vecctor position of x and y
	@oaram r - radius of our Cannon Object
	@param f - Fuel of Object
	@param sPA - Cannon barrel directional angle. 
*/

tank::tank(float x, float y, float r, float f, float sPA)
{
	position = vector(x, y);
	radius = r;
	tankFuel = f;
	playerAngle = sPA;
	colRadius = radius;
	locked = false;
	mass = radius * 100;
}

/*
	Base constructor
*/

tank::tank()
{

}

/*
	Draws the cannon barrel, base and player starting planet.
*/

void tank::draw()
{
	drawTank();
	drawCannon();
	drawPlanet();
}

/*
	Draw and display tank base on outer permimeter of starting planet. 
*/

// Draw the Player Tank
void tank::drawTank()
{
	float tankRadius = 35;

	float tankX = (radius + 15) * cos(playerAngle) + position.getX();
	float tankY = (radius + 15) * sin(playerAngle) + position.getY();

	glColor3f(0.6, 0.6, 0.6);
	glPointSize(5);
	glBegin(GL_POLYGON);
	glVertex2f((tankRadius)* cos(M_PI * 0.25 + playerAngle) + tankX, (tankRadius)* sin(M_PI * 0.25 + playerAngle) + tankY);
	glVertex2f((tankRadius)* cos(M_PI * 0.75 + playerAngle) + tankX, (tankRadius)* sin(M_PI * 0.75 + playerAngle) + tankY);
	glVertex2f((tankRadius)* cos(M_PI * 1.25 + playerAngle) + tankX, (tankRadius)* sin(M_PI * 1.25 + playerAngle) + tankY);
	glVertex2f((tankRadius)* cos(M_PI * 1.75 + playerAngle) + tankX, (tankRadius)* sin(M_PI * 1.75 + playerAngle) + tankY);
	glEnd();
}

/*
	Draw and display player starting planet.
*/

// Draw the Player Starting Planet
void tank::drawPlanet()
{
	int NPoints = 64;
	float TWOPI = M_PI * 2;
	float steps = TWOPI / NPoints;
	
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	for (float angle = 0; angle < TWOPI; angle += steps)
	{
		glVertex2f(radius * cos(angle) + position.getX(), radius * sin(angle) + position.getY());
	}
		
	glEnd();

	glLineWidth(0.1);
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINE_LOOP);
	for (float angle = 0; angle < TWOPI; angle += steps)
	{
		glVertex2f(radius * cos(angle) + position.getX(), radius * sin(angle) + position.getY());
	}


	glEnd();
	glLineWidth(0);
}


/*
	Draw and display the whole tank cannon.
*/

// Draw the tank cannon

void tank::drawCannon()
{
	float cannonRadius = 20;

	float cannonX = (radius + 30) * cos(playerAngle) + position.getX();
	float cannonY = (radius + 30) * sin(playerAngle) + position.getY();

	cannonPosition = vector(cannonX, cannonY);

	int NPoints = 32;
	float TWOPI = M_PI * 2;
	float steps = TWOPI / NPoints;

/*
	Draw and display circular cannon base.
*/

// Draw Tank Circular Cannon Base

	glColor3f(0.1, 0.1, 0.1);
	glPointSize(5);
	glBegin(GL_POLYGON);
	for (float angle = 0; angle < TWOPI; angle += steps)
	{
		glVertex2f(cannonRadius * cos(angle) + cannonX, cannonRadius * sin(angle) + cannonY);
	}
	glEnd();

	// Draw tank circular base  outline
	glColor3f(0.8, 0.8, 0.8);
	glPointSize(5);
	glBegin(GL_LINE_LOOP);
	for (float angle = 0; angle < TWOPI; angle += steps)
	{
		glVertex2f(cannonRadius * cos(angle) + cannonX, cannonRadius * sin(angle) + cannonY);
	}
	glEnd();

/*
	Draw and display tank barrel.
*/

// Draw Tank Barrel

	float correctionAngle = 0;
	
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(20 * cos(M_PI * 1.65 + playerAngle - cannonRotate - (correctionAngle)) + cannonX, 20 * sin(M_PI * 1.65 + playerAngle - cannonRotate - (correctionAngle)) + cannonY);
	glVertex2f(60 * cos(M_PI * 1.925 + playerAngle - cannonRotate - (correctionAngle)) + cannonX, 60 * sin(M_PI * 1.925 + playerAngle - cannonRotate - (correctionAngle)) + cannonY);
	glVertex2f(60 * cos(M_PI * 0.075 + playerAngle - cannonRotate - (correctionAngle)) + cannonX, 60 * sin(M_PI * 0.075 + playerAngle - cannonRotate - (correctionAngle)) + cannonY);
	glVertex2f(20 * cos(M_PI * 0.35 + playerAngle - cannonRotate - (correctionAngle)) + cannonX, 20 * sin(M_PI * 0.35 + playerAngle - cannonRotate - (correctionAngle)) + cannonY);
	glEnd();

	// Draw outline for tank barrel.
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_LINE_LOOP);
	glVertex2f(20 * cos(M_PI * 1.65 + playerAngle - cannonRotate - (correctionAngle)) + cannonX, 20 * sin(M_PI * 1.65 + playerAngle - cannonRotate - (correctionAngle)) + cannonY);
	glVertex2f(60 * cos(M_PI * 1.925 + playerAngle - cannonRotate - (correctionAngle)) + cannonX, 60 * sin(M_PI * 1.925 + playerAngle - cannonRotate - (correctionAngle)) + cannonY);
	glVertex2f(60 * cos(M_PI * 0.075 + playerAngle - cannonRotate - (correctionAngle)) + cannonX, 60 * sin(M_PI * 0.075 + playerAngle - cannonRotate - (correctionAngle)) + cannonY);
	glVertex2f(20 * cos(M_PI * 0.35 + playerAngle - cannonRotate - (correctionAngle)) + cannonX, 20 * sin(M_PI * 0.35 + playerAngle - cannonRotate - (correctionAngle)) + cannonY);
	glEnd();
}

/*
	User control to rotate Cannon Head between -1 and 1 range. 
	Controls cannon shooting mechanisms and locks cannon control (to transfer to Lunar-lander) when user shoots.
	Cannon fuel consumption calculation when moving cannon angle on starting planet & when moving cannon barrel head. 
*/

// Tank Cannon Head Rotate speed + Fuel Control
void tank::updateTank()
{
	if (Shoot)
	{
		setLock(true);

	}
	if (!locked)
	{
		if (tankFuel > 0)
		{
			if (turningLeft)
			{
				tankFuel -= 0.1;
				playerAngle -= 0.01;

			}

			else if (turningRight)
			{
				tankFuel -= 0.1;
				playerAngle += 0.01;
			}

			if (increaseAngleCannon)
			{
				tankFuel -= 0.0322;
				cannonRotate += 0.02;

				if (cannonRotate > 1)
				{
					cannonRotate = 1;
				}
			}

			else if (decreaseAngleCannon)
			{
				tankFuel -= 0.0322;
				cannonRotate -= 0.02;

				if (cannonRotate < -1)
				{
					cannonRotate = -1;

				}
			}
		}
	}	
}

/*
	Keyboard control for cannon base angle movement, cannon barrel angle movement and shooting cannon to release Lunar-lander.  
*/

// Keyboard Event

void tank::controlEvent(unsigned char k, bool pressed)
{
	if (pressed)
	{
		switch (k)
		{
		case 'a':
			turningLeft = true;
			break;
		case 'd':
			turningRight = true;
			break;
		case 'w':
			increaseAngleCannon = true;
			break;
		case 's':
			decreaseAngleCannon = true;
			break;
		case ' ':
			Shoot = true;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (k)
		{
		case 'a':
			turningLeft = false;
			break;
		case 'd':
			turningRight = false;
			break;
		case 'w':
			increaseAngleCannon = false;
			break;
		case 's':
			decreaseAngleCannon = false;
			break;
		default:
			break;
		}
	}
}

/*
	Function to set Fuel level of cannon.
	@return fuel amount.

*/

float tank::getFuel()
{
	return tankFuel;
}

/*
	Function to check if Lunar-lander is released as a bool.
	@return release of Lunar-lander when cannon is shot by user.
*/

bool tank::checkRocketRelease()
{
	return releasedRocket;
}

/*
	Bool to determine cannon shooting
	@param r  rocket release.
*/


void tank::setRocketRelease(bool r)
{
	releasedRocket = r;
}

/*
	Functiont to get Cannon barrel angle.
	@return cannon base position relative to the starting planet + cannon barrel rotate angle.
*/

float tank::getCannonAngle()
{
	return playerAngle + cannonRotate;
}

/*
	Function to get Inverse Cannon barrel angle.
	@return cannon base position relative to the starting planet - cannon barrel rotate angle.
*/

float tank::getInverseCannonAngle()
{
	return playerAngle - cannonRotate;
}

/*
	Function to set new cannon barrel angle.
	@return Cannon barrel rotated angle.
*/

float tank::getCannonRotate()
{
	return cannonRotate;
}

/*
	Function to set new cannon base angle relative to starting planet.
	@return Cannon base rotated angle.
*/

float tank::getPlayerAngle()
{
	return playerAngle;
}

/*
	Deconstructor
*/

tank::~tank()
{

}