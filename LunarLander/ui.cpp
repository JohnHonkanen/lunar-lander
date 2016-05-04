#include "ui.h"

/*
	Base Constructor
*/

UIManager::UIManager()
{
}

/*
	Deconstructor
*/

UIManager::~UIManager()
{
}

/*
	Function to Draw pointer to target goal destination Object and obstacle Object nearby + calculate the distance to it.
	@param radius - radius of directional pointer from origin.
	@param angleToTarget - angle to target location
	@param position - vector position of the origin.
	@param color3 - 3D Vector color of directional pointer RGB.
	@param textColor - 3D Vector color of text of directional pointer RGB.
	@param distance - distance to Object. 
*/

void UIManager::DrawPointers(float radius, float angleToTarget, vector position, vector color3, vector textColor, float distance)
{
	glColor3f(color3.getX(), color3.getY(), color3.getZ());
	glBegin(GL_POLYGON);
	glVertex2f((radius+20) * cos(M_PI + angleToTarget - 0.1) + position.getX(), (radius + 20) * sin(M_PI + angleToTarget - 0.1) + position.getY());
	glVertex2f((radius + 30) * cos(M_PI + angleToTarget) + position.getX(), (radius + 30) * sin(M_PI + angleToTarget) + position.getY());
	glVertex2f((radius + 20) * cos(M_PI + angleToTarget + 0.1) + position.getX(), (radius + 20) * sin(M_PI + angleToTarget + 0.1) + position.getY());
	glEnd();
	glColor3f(textColor.getX(), textColor.getY(), textColor.getZ());
	displayFloat(GLUT_BITMAP_HELVETICA_12, (radius + (35 * (radius/20))) * cos(M_PI * 1 + angleToTarget) + position.getX(), (radius + (35 * (radius / 20))) * sin(M_PI * 1 + angleToTarget) + position.getY(),distance);
}

/*
	Write text to screen
	@param *font - font of text
	@param x - position x coordinate.
	@param y - position y coordinate.
	@param *str - text to display
*/

void UIManager::drawString(void *font, float x, float y, const char *str)
{
	char *ch;
	glRasterPos3f(x, y, 0.0);
	for (ch = (char*)str; *ch; ch++)
		glutBitmapCharacter(font, (int)*ch);
}

/*
	Convert float to char and display text. 
	Write text to screen
	@param *font - font of text
	@param x - position x coordinate.
	@param y - position y coordinate.
	@param num - number to be converted to text.
*/

void UIManager::displayFloat(void *font, float x, float y, float num)
{
	std::ostringstream buffer;
	buffer << num;
	drawString(font, x, y, buffer.str().c_str());
}

/*
	Draw and display UI circle outlines. 
	@param x - position x coordinate.
	@param y - position y coordinate.
	@param verts - number of vertices
	@param r - radius of object
	@param c - 3D vector color of object RGB. 
	@param fill - to fill or not to fill the object as true or false. 
	@param lw - line width
*/

void UIManager::drawCircle(float x, float y, int verts, float r, vector c, bool fill, int lw)
{
	int NPoints = verts;
	float TWOPI = M_PI * 2;
	float steps = TWOPI / NPoints;

	glColor3f(c.getX(), c.getY(), c.getZ());
	if (fill)
	{
		glBegin(GL_POLYGON);
	}
	else
	{
		glLineWidth(lw);
		glBegin(GL_LINE_LOOP);
	}
	for (float angle = 0; angle < TWOPI; angle += steps)
	{
		glVertex2f(r * cos(angle) + x, r * sin(angle) + y);
	}


	glEnd();
}

/*
	Draw and display an arrow.
	@param x - position x coordinate.
	@param y - position y coordinate.
	@param r - radius of object.
	@param a - angle to point at.
	@param c - 3D vector color of object RGB.
*/

void UIManager::drawArrow(float x, float y, float r, float a, vector c)
{
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(r * cos(a) + x, r* sin(a) + y);
	glVertex2f((r-5) * cos(a + 0.2) + x, (r-5)* sin(a + 0.2) + y);
	glVertex2f(r * cos(a) + x, r* sin(a) + y);
	glVertex2f((r - 5) * cos(a - 0.2) + x, (r - 5)* sin(a - 0.2) + y);
	glVertex2f(r * cos(a) + x, r* sin(a) + y);
	glEnd();
}