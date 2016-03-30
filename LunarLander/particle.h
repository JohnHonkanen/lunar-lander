#pragma once
#include "vector.h"
#include <cmath>
#include <gl/freeglut.h>


class particle
{
public:
	particle();
	particle(float x, float y, float speed, float direction, float grav);
	~particle();

	void accelerate(vector);
	float angleTo(particle);
	float distanceTo(particle);
	void gravitateTo(particle);
	virtual void update();
	virtual void draw();

	float mass = 1;
	float radius = 0;
	float bounce = -1;
	float rotation = 0;

	vector position;
	vector velocity;
	vector gravity;

private:
};