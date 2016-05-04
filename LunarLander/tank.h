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
	
	void setRocketRelease(bool);
	bool checkRocketRelease();
	float getCannonAngle();
	float getInverseCannonAngle();
	float getCannonRotate();
	float getPlayerAngle();
	float getFuel();

	float playerAngle = 0;
	
	vector cannonPosition;

private:
	bool turningLeft = false;
	bool turningRight = false;
	bool increaseAngleCannon = false;
	bool decreaseAngleCannon = false;
	bool Shoot = false;
	bool releasedRocket = false;

	float cannonRotate = 0;
	float cannonLength;
	float tankFuel;
};
