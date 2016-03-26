#pragma once
#define _USE_MATH_DEFINES
#include "vector.h"
#include <cmath>
#include <gl/freeglut.h>


class Rocket
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
	vector position = vector();
	vector velocity = vector();
	vector gravity = vector();

private:
	bool accelerating = false;
	bool turningLeft = false;
	bool turningRight = false;
	bool deacclerating = false;
};