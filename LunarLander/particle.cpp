#include <cmath>
#include "particle.h"

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
	return atan2(p2.position.getY() - position.getY(), p2.position.getX() - position.getX());
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

particle::~particle()
{
}