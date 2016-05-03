#pragma once
#include "vector.h"
#include <cmath>
#include <gl/freeglut.h>
#include <iostream>


class particle
{
public:
	particle();
	particle(float x, float y, float speed, float direction, float grav);
	~particle();

	virtual void update(); //Physics Calculation
	virtual void draw(); //Draw our Particle to screen

	void gravitateTo(particle);
	void collision(particle, float facingAngle, bool isTarget); //Add Collision to our Particle
	bool checkCollision(particle); //Check if Colliding
	void setColor(vector color3D); //Set our Color using a 3D vector

	//Locking Mechanims
	void setLock(bool lock);
	bool getLock();

	float distanceTo(particle);
	float getAngleToTarget(particle); //Find Angle to Particle

	float radius = 0;
	float colRadius = 0; //Collision Radius
	float mass = 1; // Mass for our Gravitational Pull Calculation

	vector position; //Position on Screen

protected:
	virtual void accelerate(vector);

	float angleTo(particle);
	vector calculateCollisionPoint(particle); //Find our point of collision
	void checkBackCollision(particle, float angle, bool isTarget);

	vector velocity;
	vector gravity;
	vector color;

	bool locked = true; //Set our Particle to not be affected by physics.
	bool crashed = false; // Check if our particle Crashed
	bool landed = false; // Particle Safely landed

	float angleToTarget = 0;

private:

	float rotation = 0;

};