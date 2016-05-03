#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <gl/freeglut.h>
#include "particle.h"
#include "tank.h"


class Rocket: public particle
{
public:
	Rocket(float x, float y, float fuel, float accelerationSpeed, float maxSpeed);
	Rocket();
	~Rocket();

	void controlEvent(unsigned char, bool);
	void draw(); // Draw our Rocket
	void update(); //Update our Position
	void update(particle, bool isTarget); //Update our Collision
	float getAngleToTarget(particle); //Find Angle to Particle
	void follow(tank);
	float getFuel();
	float getVelocity();
	void setFuel(float fuel);
	float getVelocityAngle();
	bool checkDampeners();
	bool checkCrashed();
	bool checkLanded();

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
	bool shot = false;
	bool dampeners = false;
	float angleToTarget = 0;
};