#define _USE_MATH_DEFINES

#include <cmath>
#include <gl/freeglut.h>
#include "particle.h"



particle::particle(){}
particle::particle(float x, float y, float speed, float direction, float grav)
{
	position = vector(x, y);
	velocity = vector(0, 0);
	velocity.setLength(speed);
	velocity.setAngle(direction);
	gravity = vector(0, grav || 0);
}

void particle::accelerate(vector accel)
{
	velocity.addTo(accel);
}

void particle::update()
{
	velocity.addTo(gravity);
	position.addTo(velocity);
}

float particle::angleTo(particle p2)
{
	return -atan2f(p2.position.getY() - position.getY(), p2.position.getX() - position.getX())+ M_PI /2;
}

float particle::distanceTo(particle p2)
{
	float dx = p2.position.getX() - position.getX();
	float dy = p2.position.getY() - position.getY();

	return sqrt(dx*dx + dy*dy);
}

void particle::gravitateTo(particle p2)
{
	vector grav = vector(0, 0);
	float dist = distanceTo(p2);

	grav.setLength(p2.mass / (dist * dist));
	grav.setAngle(angleTo(p2));

	velocity.addTo(grav);

}

void particle::draw()
{
	glPointSize(0.1);
	const int NPOINTS = 8;
	const float TWOPI = 2 * 3.14159268;
	const float STEP = TWOPI / NPOINTS;
	glBegin(GL_POLYGON);
	for (float angle = 0; angle<TWOPI; angle += STEP)
		glVertex2f(radius * cos(angle) + position.getX(), radius * sin(angle) + position.getY());
	glEnd();
}

particle::~particle()
{
}