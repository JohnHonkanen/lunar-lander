#include <GL/freeglut.h>
#include "particle.h"

class camera2d
{
public:
	camera2d();
	camera2d(particle);
	~camera2d();

private:
	vector position;
	vector target;
	vector dir;

	vector cameraRight;
	vector cameraUp;


};

camera2d::camera2d()
{
	position = vector(0.0f, 0.0f, 0.0f);
	target = vector(0.0f, 0.0f, 0.0f);
	dir = position.subtract(target);
	dir = dir.normalize();

	vector up = vector(0.0f, 1.0f);
	cameraRight = up.cross(dir);
	cameraRight = cameraRight.normalize();

	cameraUp = dir.cross(cameraRight);
	cameraUp = cameraUp.normalize();
}

camera2d::camera2d(particle p)
{
	position = vector(0.0f, 0.0f, 0.0f);
	target = p.position;
	dir = position.subtract(target);
	dir = dir.normalize();
}

camera2d::~camera2d()
{
}