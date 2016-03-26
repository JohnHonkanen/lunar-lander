#pragma once
#define _USE_MATH_DEFINES
#include "vector.h"
class particle
{
public:
	particle();
	particle(float, float, float, float, float);
	~particle();

	void accelerate(vector);
	void update();
	float angleTo(particle);
	float distanceTo(particle);
	void gravitateTo(particle);
	void draw();

	float mass = 1;
	float radius = 0;
	float bounce = -1;
	float rotation = 0;

	vector position = vector();
	vector velocity = vector();
	vector gravity = vector();

private:
};