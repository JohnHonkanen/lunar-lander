#include "moon.h"
int randR(int min, int max)
{
	return rand() % ((max + 1) - min) + min;
}


Moon::Moon()
{

}
Moon::Moon(vector pos, float r, float speed, float direction, float grav, int numVerts)
{
	position = pos;
	velocity = vector(0, 0);
	velocity.setLength(speed);
	velocity.setAngle(direction);
	gravity = vector(0, grav || 0);
	color = vector(0.5f, 0.5f, 0.5f); //Setting the Base Color of our Moon
	numVertices = numVerts;
	vertices = new vector[numVertices+1];
	radius = r;
	mass = radius * 1;
	colRadius = radius;

	const int NPOINTS = numVertices;
	const float TWOPI = 2 * M_PI;
	const float STEP = TWOPI / NPOINTS;
	int i = 0;
	//Storing our Vertice Information
	for (float angle = 0; angle<TWOPI; angle += STEP)
	{
		float randRadius = randR(radius - 20, radius + 20);
		float x = randRadius * cos(angle) + position.getX();
		float y = randRadius * sin(angle) + position.getY();
		std::cout << x << "||" << y << "||" << angle <<std::endl;
		vertices[i] = vector(x,y);
		i++;
	}
}

void Moon::draw()
{
	glPointSize(0.1);
	glColor3f(color.getX(), color.getY(), color.getZ());
	glBegin(GL_POLYGON);
	for (int i = 0; i < numVertices; i++)
	{
		glVertex2f(vertices[i].getX(), vertices[i].getY());
	}
	glEnd();
}

Moon::~Moon()
{
}