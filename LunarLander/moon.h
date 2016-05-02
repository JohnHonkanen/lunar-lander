#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <gl/freeglut.h>
#include "particle.h"

class Moon : public particle
{
public:
	Moon();
	Moon(vector position,float radius , float speed, float direction, float grav, int numVerts);
	~Moon();

	void draw();

private:
	int numVertices; //Number of Vertices for our Moon
	vector *vertices; //Storage of Vertices Position
};