#define _USE_MATH_DEFINES

#include<gl/freeglut.h>
#include<iostream>
#include <cmath>

#include "rocket.h"


float height, width;
Rocket player;
particle moon;
particle moon2;

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	//Render Scene and Draw
	player.draw();
	moon.draw();
	moon2.draw();
	//End of Render Scene
	glFlush();
	glutSwapBuffers();

}


void idle(int value)
{

	glutTimerFunc(41, idle, 0);
	/* Calculate Physics for Frame */
	player.gravitateTo(moon);
	player.gravitateTo(moon2);
	player.update();
	std::cout << player.velocity.getLength() << std::endl;
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
	gluOrtho2D(0, width*2, 0, height*2);
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
	player = Rocket(width/ 4, height, 100, 0.1f, 10);
	moon = particle(width,height/2, 0,  0, 0);
	moon.radius = 10;
	moon.mass = 27000;

	moon2 = particle(width, height*1.5, 0, 0, 0);
	moon2.radius = 10;
	moon2.mass = 30000;
	/* End of Initialization*/

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
