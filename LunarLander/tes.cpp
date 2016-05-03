#define _USE_MATH_DEFINES

#include<gl/freeglut.h>
#include<iostream>
#include <cmath>
#include <time.h>
#include <cstring>

#include "tank.h"
#include "rocket.h"
#include "stars.h"
#include "moon.h"
#include "helperFunctions.h"
#include "ui.h"


float height, width;

Rocket player;
const int numMoons = 10;
tank artillery;

UIManager *UI;

Moon moons[numMoons];
vector moonLocation[numMoons];

const int numStars = 10000;
Star * star[numStars];

int seed;
int moonLand;

void renderScene() {

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
		if (artillery.getLock())
		{
			if (player.distanceTo(moons[i]) < 2000)
			{
				UI->DrawPointers(player.radius, player.getAngleToTarget(moons[i]), player.position, vector(1.0f, 0.0f, 0.0f), vector(1.0f, 0.0f, 0.0f), player.distanceTo(moons[i]) - moons[i].radius-player.radius);
			}
		}
	}
	
	// Draw Tank Components
	artillery.draw();

	// The actual rocket
	if (artillery.getLock())
	{
		player.draw();
		UI->DrawPointers(player.radius, player.getAngleToTarget(moons[moonLand]), player.position, vector(0.0f,0.0f,1.0f), vector(1.0f, 1.0f, 1.0f), player.distanceTo(moons[moonLand])- moons[moonLand].radius-player.radius);
	}
	
	//Main UI Draws
	vector color;
	if (player.getFuel() > 60)
	{
		color = vector(0.0f, 1.0f, 0.0f);
	}

	else if (player.getFuel() > 30 || player.getFuel() < 60)
	{
		color = vector(1.0f * (float)player.getFuel(), 1.0f * (float)player.getFuel() / 100, 0.0f);
	}
	else
	{
		color = vector(1.0f * (float)player.getFuel(), 0.0f, 0.0f);
	}
	vector UIFuel = vector(player.position.getX() + width / 2 - 50, player.position.getY() + height / 2 - 50);
	UI->drawCircle(UIFuel.getX(), UIFuel.getY() , 32, 50, color, false, 5);
	UI->displayFloat(GLUT_BITMAP_HELVETICA_18, UIFuel.getX() + 15, UIFuel.getY() - 5 , round(player.getFuel()));
	UI->drawString(GLUT_BITMAP_HELVETICA_12, UIFuel.getX() + 15, UIFuel.getY() - 25, "Litres");
	//End of UI Draws
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
	artillery.updateTank();
	if (!artillery.getLock())
	{
		player.follow(artillery);
	}
	

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
	artillery.controlEvent(key, true);
}

void keyUp(unsigned char key, int x, int y) {
	player.controlEvent(key, false);
	artillery.controlEvent(key, false);
}

int main(int argc, char** argv)
{
	height = 1000;
	width = 1000;
	//Initialize Object Data

	// Initialize Tank
	float randomAngle = (float)random(0, 200) / 10;
	artillery = tank(width * 5, height * 5, 1500, 100, randomAngle);

	player = Rocket(width * 5, height * 5, 100, 0.1f, 10);
	player.follow(artillery); //Sets initial Position to tank

	UI = new UIManager();

	moonLand = random(0, numMoons-1);
	seed = random(-123456, 123456);
	int sizeOfMoonLoc = -1;
	srand(time(NULL));
	for (int i = 0; i < numMoons; i++)
	{
		sizeOfMoonLoc++;
		moonLocation[i] = vector(random(-width * 4, width * 4), random(-height * 4, height * 4));
		float moonRadius = random(300, 500);
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
	glutCreateWindow("LUNAR ROCEKET THINGEHY");
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
