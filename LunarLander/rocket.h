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
	void update();
	void accelerate(vector);

	float fuel;
	float maxSpeed;
	float facingAngle;
	float acceleration;

	vector thrust = vector();

private:
	bool accelerating = false;
	bool turningLeft = false;
	bool turningRight = false;
	bool deacclerating = false;
};