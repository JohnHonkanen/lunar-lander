#define _USE_MATH_DEFINES

#include<gl/freeglut.h>
#include<iostream>
#include <cmath>

#include "particle.h"

float height, width;

particle sun;
particle planet;

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0.5, 0);
	sun.draw();
	glColor3f(0, 0, 1);
	planet.draw();
	glFlush();

}

void idle(int value)
{
	planet.gravitateTo(sun);
	planet.update();

	std::cout << planet.distanceTo(sun) << std::endl;
	//std::cout << planet.velocity.getX() << "||" << planet.velocity.getY() << std::endl;
	//  Call display function (draw the current frame)
	glutTimerFunc(41, idle, 0);
	glutPostRedisplay();
}

void reshape(int x, int y)
{
	width = x;
	height = y;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
}

int main(int argc, char** argv)
{
	height = 800;
	width = 800;

	sun = particle(width / 2, height / 2, 0, 0, 0);
	planet = particle(width / 2, height/ 2 + 200, 10, -M_PI / 2, 0);
	sun.mass = 15000;
	planet.mass = 100;
	sun.radius = 50;
	planet.radius = 5;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	//glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Draw Triangle");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0, width, height, 0);
	//glutReshapeFunc(reshape);
	glutDisplayFunc(renderScene);
	glutTimerFunc(41,idle,0);
	glutMainLoop();
}