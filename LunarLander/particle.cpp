#define _USE_MATH_DEFINES
#include "particle.h"

particle::particle()
{
}
particle::particle(float x, float y, float speed, float direction, float grav)
{
	position = vector(x, y);
	velocity = vector(0, 0);
	velocity.setLength(speed);
	velocity.setAngle(direction);
	gravity = vector(0, grav || 0);
	color = vector(0.5f, 0.5f, 0.5f);
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
//Gravitational Pull towards Particle
void particle::gravitateTo(particle p2)
{
	vector grav = vector(0, 0);
	float dist = distanceTo(p2);

	grav.setLength(p2.mass / (dist * dist));
	grav.setAngle(angleTo(p2));

	if(!locked)
		velocity.addTo(grav); 

}

void particle::draw()
{
	glPointSize(0.1);
	const int NPOINTS = 30;
	const float TWOPI = 2 * 3.14159268;
	const float STEP = TWOPI / NPOINTS;
	glColor3f(color.getX(), color.getY(), color.getZ());
	glBegin(GL_POLYGON);
	for (float angle = 0; angle<TWOPI; angle += STEP)
		glVertex2f(radius * cos(angle + rotation) + position.getX(), radius * sin(angle + rotation) + position.getY());
	glEnd();
}
//Check if Colliding
bool particle::checkCollision(particle col)
{
	float colDist = col.colRadius + colRadius;
	float dist = position.distance(col.position);

	if (colDist > dist)
		return true;
	return false;
}
//Find out where our Collision Point is
vector particle::calculateCollisionPoint(particle col)
{
	float collisionX = ((position.getX() * col.colRadius) + (col.position.getX() * colRadius))/ (colRadius + col.colRadius);
	float collisionY = ((position.getY() * col.colRadius) + (col.position.getY() * colRadius)) / (colRadius + col.colRadius);

	vector collisionPoint = vector(collisionX, collisionY);

	return collisionPoint;
}

void particle::checkBackCollision(particle col, float a, bool isTarget)
{
	float dx = position.getX() - col.position.getX();
	float dy = position.getY() - col.position.getY();
	float angle = atan2(dy, dx);
	int turns = ceil(abs(a) / (2 * M_PI)) - 1;
	float faceAngle = a;
	if (turns >= 1)
	{
		if (faceAngle < 0)
		{
			faceAngle = a + (M_PI * 2) * turns;
		}
		else
		{
			faceAngle = a - (M_PI * 2) * turns;
		}
	}
	float frontAngle = faceAngle - (M_PI / 2);
	float backAngle1 = frontAngle + M_PI;
	float backAngle2 = frontAngle - M_PI;

	if (velocity.getLength() < 3)
	{
		if (backAngle1 < angle + 0.6 && backAngle1 > angle - 0.6)
		{
			if (isTarget)
				landed = true;
		}
		else
		{
			crashed = true;
		}
	}
	else
	{
		crashed = true;
	}
}
//Check our Collision and Apply proper Constraints
void particle::collision(particle col, float a, bool isTarget)
{
	vector collisionPoint = calculateCollisionPoint(col);
	
	if (checkCollision(col))
	{
		checkBackCollision(col, a, isTarget);

		if (collisionPoint.getX() > position.getX())
		{
			if (velocity.getX() > 0)
				velocity.setX(0);
		}
		else if (collisionPoint.getX() < position.getX())
		{
			if (velocity.getX() < 0)
				velocity.setX(0);
		}

		if (collisionPoint.getY() < position.getY())
		{
			if (velocity.getY() < 0)
				velocity.setY(0);
		}
		else if (collisionPoint.getY() > position.getY())
		{
			if (velocity.getY() > 0)
				velocity.setY(0);
		}
	}
}
//Set Color of our Particle
void particle::setColor(vector color)
{
	this->color = color;
}

void particle::setLock(bool lock)
{
	locked = lock;
}

bool particle::getLock()
{
	return locked;
}

particle::~particle()
{
}