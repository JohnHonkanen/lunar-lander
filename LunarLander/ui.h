#pragma once
#define _USE_MATH_DEFINES

#include <gl/freeglut.h>
#include "vector.h"
#include <sstream>

class UIManager
{
public:
	UIManager();
	~UIManager();

	void DrawPointers(float radius, float angleToTarget, vector position, vector color3, vector textColor, float distance);
	void drawString(void *font, float x, float y, const char *str);
	void displayFloat(void *font, float x, float y, float num);
	void drawCircle(float x, float y, int vertices, float radius, vector color, bool fill, int lineWidth);

private:

};
