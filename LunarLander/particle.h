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

	virtual void update();
	virtual void draw();

	void gravitateTo(particle);
	void collision(particle);

	float radius = 0;
	float mass = 1;

	vector position;

protected:

	vector velocity;
	vector gravity;

private:
	void accelerate(vector);
	float angleTo(particle);
	float distanceTo(particle);
	bool checkCollision(particle);
	vector calculateCollisionPoint(particle);

	float rotation = 0;

};