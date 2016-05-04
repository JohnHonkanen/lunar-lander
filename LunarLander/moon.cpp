#include "moon.h"
int randR(int min, int max)
{
	return rand() % ((max + 1) - min) + min;
}

/*
	Base Constructor
*/
Moon::Moon()
{

}
/*
	Constructor
	@param pos	Vector position of our Moon object
	@param r	Radius of our Moon Object
	@param s	Speed of our Moon
	@param d	Directional Angle of Our Moon to move at
	@param grav	Downward Speed to affect our Moon
	@param numVerts Number of Vertices used to draw our Moon
*/

Moon::Moon(vector pos, float r, float s, float d, float grav, int numVerts)
{
	position = pos;
	velocity = vector(0, 0);
	velocity.setLength(s);
	velocity.setAngle(d);
	gravity = vector(0, grav || 0);
	color = vector(0.5f, 0.5f, 0.5f); //Setting the Base Color of our Moon
	numVertices = numVerts;
	vertices = new vector[numVertices+1];
	radius = r;
	mass = radius * 1000;
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
		vertices[i] = vector(x,y);
		i++;
	}
}
/*
	Draws and Display our Moon Object
*/
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
/*
	Deconstructor
*/
Moon::~Moon()
{
}