#define _USE_MATH_DEFINES

#include<gl/freeglut.h>
#include<iostream>
#include <cmath>

#include "rocket.h"

float height, width;
Rocket player;

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	//Render Scene and Draw
	player.draw();
	glFlush();

}


void idle(int value)
{

	glutTimerFunc(41, idle, 0);
	//Calculate Physics for Frame
	player.update();
	std::cout << player.velocity.getLength() << std::endl;
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
	/*Initialize Object Data*/
	player = Rocket(height / 2, width / 2, 100, 0.1f, 10);
	/* End of Initialization*/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
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
