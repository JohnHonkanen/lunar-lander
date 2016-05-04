#define _USE_MATH_DEFINES
#include "particle.h"

particle::particle()
{
}
/*
	Particle Constructor
	@param x	X coordinate on Screen
	@param y	Y Coordinate on Screen
	@param s	Speed of our Particle
	@param d	Directional Angle of our Particle
	@param grav	Gravitation Pull in Y direction
*/
particle::particle(float x, float y, float s, float d, float grav)
{
	position = vector(x, y);
	velocity = vector(0, 0);
	velocity.setLength(s);
	velocity.setAngle(d);
	gravity = vector(0, grav || 0);
	color = vector(0.5f, 0.5f, 0.5f);
}
/*
	Accelerate our Particle towards a Direction using Vector
	@param accel	Vector with Magnitude and Angle
*/
void particle::accelerate(vector accel)
{
	velocity.addTo(accel);
}

/*
	Update Physics and Screen Location to our Particle
*/
void particle::update()
{
	velocity.addTo(gravity);
	position.addTo(velocity);
}
/*
	Calculate the Angle from this particle to another particle
	@param p2	Particle to caculate angle to
	@return		Angle to our Particle p2
*/
float particle::angleTo(particle p2)
{
	return -atan2f(p2.position.getY() - position.getY(), p2.position.getX() - position.getX())+ M_PI /2;
}
/*
	Calculate the Distance from this particle to another particle
	@param p2	Particle to caculate distance to
	@return		Distance to our Particle p2
*/
float particle::distanceTo(particle p2)
{
	float dx = p2.position.getX() - position.getX();
	float dy = p2.position.getY() - position.getY();

	return sqrt(dx*dx + dy*dy);
}
/*
	Calculate and Add Gravitational pull to our Velocity based on Mass of a Particle to this Particle using Vectors
	@param p2	Particle to Gravitate to.
*/
void particle::gravitateTo(particle p2)
{
	vector grav = vector(0, 0);
	float dist = distanceTo(p2);

	grav.setLength(p2.mass / (dist * dist));
	grav.setAngle(angleTo(p2));

	if(!locked)
		velocity.addTo(grav); 

}
/*
	Draw a circle to represent our particle
*/
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
/*
	Check if a particle is colliding to this particle (Circle - Circle Collision)
	@param col	Particle to check collision against
	@return		Colliding Results, True or False.
*/
bool particle::checkCollision(particle col)
{
	float colDist = col.colRadius + colRadius;
	float dist = position.distance(col.position);

	if (colDist > dist)
		return true;
	return false;
}
/*
	Find our Point of Collision
	@param col	Particle to check our Collision against
	@return		Collision Point between our two Particles	
*/
vector particle::calculateCollisionPoint(particle col)
{
	float collisionX = ((position.getX() * col.colRadius) + (col.position.getX() * colRadius))/ (colRadius + col.colRadius);
	float collisionY = ((position.getY() * col.colRadius) + (col.position.getY() * colRadius)) / (colRadius + col.colRadius);

	vector collisionPoint = vector(collisionX, collisionY);

	return collisionPoint;
}
/*
	Check to see if we are colliding with the Back of the Particle
	Win and Lose Condition for the Game
	@param col	Particle to check collision against
	@param a	Current Facing Angle of Particle (Rocket Class)
	@param isTarget	Win Condition of our Game. if True.
*/
void particle::checkBackCollision(particle col, float a, bool isTarget)
{
	float dx = position.getX() - col.position.getX();
	float dy = position.getY() - col.position.getY();
	float angle = atan2(dy, dx);
	int turns = ceil(abs(a) / (2 * M_PI)) - 1;
	float faceAngle = a;
	//Normalizing our Angle faceAngle (0 - 2PI)
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
	//Setting and Adjusting our Angles to Grid
	float frontAngle = faceAngle - (M_PI / 2);
	float backAngle1 = frontAngle + M_PI;
	float backAngle2 = frontAngle - M_PI;

	if (velocity.getLength() < 6)
	{
		if (backAngle1 < angle + 0.6 && backAngle1 > angle - 0.6)
		{
			if (isTarget)
				landed = true;
		}
		else if (backAngle2 < angle + 0.6 && backAngle2 > angle - 0.6)
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

/*
	Apply our Collision and Collision check for win Conditions
	@param col	Particle to check Collision with
	@param a	Current Facing Angle of Particle (Rocket Class) for checkBackCollision
	@param isTarget	Win Condition of our Game. if True. for checkBackCollision
*/
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
/*
	Set the Color of our Particle
	@param color	3D Vector to set our Color in RGB
*/
void particle::setColor(vector color)
{
	this->color = color;
}
/*
	Lock our Particle from Physics (Use for Derived Classes)
	@param lock	Set True or False
*/
void particle::setLock(bool lock)
{
	locked = lock;
}
/*
	Check if our Particle is Locked from Physics
	@return True or False
*/
bool particle::getLock()
{
	return locked;
}

/*
	Calculate and Adjust the Angle to our Grid to Target
	@param p	Particle to check Angle with
	@return		Adjusted Angle to Target
*/
float particle::getAngleToTarget(particle p)
{
	float angle = angleTo(p);
	angleToTarget = -angle - M_PI / 2;
	return angleToTarget;
}

/*
	Set Velocity for our particle
	@param m	Magnitude of our Velocity Vector
	@param a	Angle of our Velocity Vector
*/
void particle::setVelocity(float m, float a)
{
	velocity.setLength(m);
	velocity.setAngle(a);
}
particle::~particle()
{
}