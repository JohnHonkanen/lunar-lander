#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <gl/freeglut.h>
#include "particle.h"


class Rocket: public particle
{
public:
	Rocket(float, float, float, float, float);
	Rocket();
	~Rocket();

	void controlEvent(unsigned char, bool);
	void draw();
	void drawPointer();
	void update();
	void update(particle);
	void updatePointer(particle);

private:

	void accelerate(vector);
	void updateVelocity();
	void updatePosition();

	vector thrust = vector();
	float fuel;
	float maxSpeed;
	float facingAngle;
	float acceleration;
	bool accelerating = false;
	bool turningLeft = false;
	bool turningRight = false;
	bool deacclerating = false;
	bool dampeners = false;
	float angleToTarget = 0;
};