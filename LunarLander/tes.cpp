#define _USE_MATH_DEFINES

#include<gl/freeglut.h>
#include<iostream>
#include <cmath>
#include <time.h>

#include "rocket.h"
#include "stars.h"
#include "moon.h"
#include "helperFunctions.h"


float height, width;

Rocket player;
const int numMoons = 10;
Moon moons[numMoons];
vector moonLocation[numMoons];

const int numStars = 10000;
Star * star[numStars];

int seed;
int moonLand;

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	//Camera Follow
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(player.position.getX()+width/2, player.position.getY()-height/2, 0,
		player.position.getX()+width/2, player.position.getY() - height/2,10,
		0,1,0);
	//Render Scene and Draw
	for (int i = 0; i < numStars; i++)
	{
		star[i]->draw();
	}
	for (int i = 0; i < numMoons; i++)
	{
		moons[i].draw();
	}
	
	player.draw();
	//End of Render Scene
	glutSwapBuffers();

}


void idle(int value)
{

	glutTimerFunc(41, idle, 0);
	/* Calculate Physics for Frame */
	for (int i = 0; i < numStars; i++)
	{
		star[i]->update();
	}
	for (int i = 0; i < numMoons; i++)
	{
		player.gravitateTo(moons[i]);
		player.update(moons[i]);
	}
	player.update();
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
	moonLand = random(0, numMoons-1);
	seed = random(-123456, 123456);
	int sizeOfMoonLoc = -1;
	srand(time(NULL));
	for (int i = 0; i < numMoons; i++)
	{
		sizeOfMoonLoc++;
		moonLocation[i] = vector(random(-width * 4, width * 4), random(-height * 4, height * 4));
		float moonRadius = random(300, 1000);
		moons[i] = Moon(moonLocation[i], moonRadius, 0, 0, 0, 60);

		for (int z = 0; z < sizeOfMoonLoc; z++)
		{
			if (z != i)
			{
				while (moons[i].checkCollision(moons[z]))
				{
					moonLocation[i] = vector(random(-width * 4, width * 4), random(-height * 4, height * 4));
					moons[i] = Moon(moonLocation[i], moonRadius, 0, 0, 0, round(moonRadius / 10));
				}
			}
		}
	}
	for (int i = 0; i < numStars; i++)
	{
		star[i] = new Star(vector(random(-width*8,width*8), random(-height*8,height*8)), vector(0.8f, 0.8f, 0.0f), random(3, 15), random(0,100));
	}
	//End of Initialization

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Draw Triangle");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.05, 0.05, 0.05, 0.0);
	//gluOrtho2D(0, width, height, 0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(41,idle,0);
	glutMainLoop();
}
