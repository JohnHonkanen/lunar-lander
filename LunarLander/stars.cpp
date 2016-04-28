#include "stars.h"

Star::Star()
{

}

Star::Star(vector position, vector color, float radius, float startGlow)
{
	this->position = position;
	this->color = color;
	this->radius = radius;
	glowAlphaSin = startGlow/100;
}

void Star::update()
{
	glowAlpha = sin(glowAlphaSin);
	if (glowAlpha < 0.10f)
	{
		glowAlphaSin += 0.2;
	}
	glowAlphaSin += 0.05;
}

void Star::draw()
{
	const int NPOINTS = 30;
	const float TWOPI = 2 * M_PI;
	const float STEP = TWOPI / NPOINTS;
	//Glow
	glColor4f(color.getX(), color.getY(), color.getZ(), glowAlpha);
	glBegin(GL_LINE_LOOP);
	glVertex2f(radius * cos(M_PI * 0.00) + position.getX(), radius * sin(M_PI * 0.00) + position.getY());
	glVertex2f(radius/2 * cos(M_PI * 0.25) + position.getX(), radius/2 * sin(M_PI * 0.25) + position.getY());
	glVertex2f(radius * cos(M_PI * 0.50) + position.getX(), radius * sin(M_PI * 0.50) + position.getY());
	glVertex2f(radius / 2 * cos(M_PI * 0.75) + position.getX(), radius / 2 * sin(M_PI * 0.75) + position.getY());
	glVertex2f(radius * cos(M_PI * 1.00) + position.getX(), radius * sin(M_PI * 1.00) + position.getY());
	glVertex2f(radius / 2 * cos(M_PI * 1.25) + position.getX(), radius / 2 * sin(M_PI * 1.25) + position.getY());
	glVertex2f(radius * cos(M_PI * 1.50) + position.getX(), radius * sin(M_PI * 1.50) + position.getY());
	glVertex2f(radius / 2 * cos(M_PI * 1.75) + position.getX(), radius / 2 * sin(M_PI * 1.75) + position.getY());
	glEnd();


}
Star::~Star()
{
}