#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/freeglut.h>
#include "particle.h"

class tank : public particle
{
public:
	tank();
	tank(float x, float y, float planetRadius, float tankFuel, float startPlayerAngle);
	void drawTank();
	void drawPlanet();
	void updateTank();
	void drawCannon();
	void controlEvent(unsigned char key, bool keyPressed);
	void draw();

	float playerAngle = 0;
	

private:
	bool turningLeft = false;
	bool turningRight = false;
	bool increaseAngleCannon = false;
	bool decreaseAngleCannon = false;

	float cannonRotate = 0;
	float cannonLength;
	float tankFuel;

};
