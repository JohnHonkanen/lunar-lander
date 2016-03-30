#define _USE_MATH_DEFINES

#include<gl/freeglut.h>
#include<iostream>
#include <cmath>

#include "rocket.h"


float height, width;

Rocket player;
particle moon;

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	//Camera Follow
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(player.position.getX()+width/2, player.position.getY()-height/2, 0,
		player.position.getX()+width/2, player.position.getY() - height/2,10,
		0,1,0);
	//Render Scene and Draw
	player.draw();
	moon.draw();
	//End of Render Scene
	glutSwapBuffers();

}


void idle(int value)
{

	glutTimerFunc(41, idle, 0);
	/* Calculate Physics for Frame */
	player.gravitateTo(moon);
	player.update();
	std::cout << player.position.getX() << "||" << player.position.getY() << std::endl;
	/* End of Calculation */
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

void keyDown(unsigned char key, int x, int y)
{
	player.controlEvent(key, true);
}

void keyUp(unsigned char key, int x, int y) {
	player.controlEvent(key, false);
}

int main(int argc, char** argv)
{
	height = 1000;
	width = 1000;
	//Initialize Object Data
	player = Rocket(width/2, height, 100, 0.1f, 10);
	moon = particle(width/2,height/2, 0,  0, 0);
	moon.radius = 100;
	moon.mass = 15000;

	//End of Initialization

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Draw Triangle");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//gluOrtho2D(0, width, height, 0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(41,idle,0);
	glutMainLoop();
}
