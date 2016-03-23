#pragma once
#include "vector.h"
class particle
{
public:
	particle(float, float, float, float, float);
	~particle();

	void accelerate(vector);
	void update();
	float angleTo(particle);
	float distanceTo(particle);
	void gravitateTo(particle);

private:
	vector position = vector();
	vector velocity = vector();
	float mass = 1;
	float radius = 0;
	float bounce = -1;
	vector gravity = vector();
};