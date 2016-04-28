#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <gl/freeglut.h>
#include "particle.h"

class Star : public particle
{
public:
	Star(vector position, vector color, float radius, float startGlow);
	Star();
	~Star();

	void update();
	void draw();

private:
	float glowAlphaSin;
	float glowAlpha;
};