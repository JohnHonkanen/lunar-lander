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

	virtual void update();
	virtual void draw();

	void gravitateTo(particle);
	void collision(particle);
	bool checkCollision(particle);
	void setColor(vector color3D);

	float radius = 0;
	float colRadius = 0;
	float mass = 1;

	vector position;

protected:
	virtual void accelerate(vector);

	float angleTo(particle);
	float distanceTo(particle);
	vector calculateCollisionPoint(particle);

	vector velocity;
	vector gravity;
	vector color;

private:

	float rotation = 0;

};