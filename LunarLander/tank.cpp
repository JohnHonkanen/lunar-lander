#include "tank.h"

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

tank::tank()
{

}

void tank::draw()
{
	drawTank();
	drawCannon();
	drawPlanet();
}

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


// Draw Tank Square Base

void tank::drawCannon()
{
	float cannonRadius = 20;

	float cannonX = (radius + 30) * cos(playerAngle) + position.getX();
	float cannonY = (radius + 30) * sin(playerAngle) + position.getY();

	int NPoints = 32;
	float TWOPI = M_PI * 2;
	float steps = TWOPI / NPoints;



// Draw Tank Circular Cannon Base

	glColor3f(0.1, 0.1, 0.1);
	glPointSize(5);
	glBegin(GL_POLYGON);
	for (float angle = 0; angle < TWOPI; angle += steps)
	{
		glVertex2f(cannonRadius * cos(angle) + cannonX, cannonRadius * sin(angle) + cannonY);
	}
	glEnd();

	glColor3f(0.8, 0.8, 0.8);
	glPointSize(5);
	glBegin(GL_LINE_LOOP);
	for (float angle = 0; angle < TWOPI; angle += steps)
	{
		glVertex2f(cannonRadius * cos(angle) + cannonX, cannonRadius * sin(angle) + cannonY);
	}
	glEnd();

// Draw Tank Barrel

	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(20 * cos(M_PI * 1.65 + playerAngle + cannonRotate) + cannonX, 20 * sin(M_PI * 1.65 + playerAngle + cannonRotate) + cannonY);
	glVertex2f(60 * cos(M_PI * 1.925 + playerAngle + cannonRotate) + cannonX, 60 * sin(M_PI * 1.925 + playerAngle + cannonRotate) + cannonY);
	glVertex2f(60 * cos(M_PI * 0.075 + playerAngle + cannonRotate) + cannonX, 60 * sin(M_PI * 0.075 + playerAngle + cannonRotate) + cannonY);
	glVertex2f(20 * cos(M_PI * 0.35 + playerAngle + cannonRotate) + cannonX, 20 * sin(M_PI * 0.35 + playerAngle + cannonRotate) + cannonY);
	glEnd();

	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_LINE_LOOP);
	glVertex2f(20 * cos(M_PI * 1.65 + playerAngle + cannonRotate) + cannonX, 20 * sin(M_PI * 1.65 + playerAngle + cannonRotate) + cannonY);
	glVertex2f(60 * cos(M_PI * 1.925 + playerAngle + cannonRotate) + cannonX, 60 * sin(M_PI * 1.925 + playerAngle + cannonRotate) + cannonY);
	glVertex2f(60 * cos(M_PI * 0.075 + playerAngle + cannonRotate) + cannonX, 60 * sin(M_PI * 0.075 + playerAngle + cannonRotate) + cannonY);
	glVertex2f(20 * cos(M_PI * 0.35 + playerAngle + cannonRotate) + cannonX, 20 * sin(M_PI * 0.35 + playerAngle + cannonRotate) + cannonY);
	glEnd();
}

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

float tank::getFuel()
{
	return tankFuel;
}