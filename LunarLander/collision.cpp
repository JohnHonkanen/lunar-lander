#include "vector.h"

enum collisionType
{
	circle,
	rectangle,
	point,
};

class collision
{
public:
	collision();
	~collision();
	void setWidth(float width);
	void setHeight(float height);
	void setRadius(float radius);
	void setPosition(vector pos);

	float getRadius();
	vector getPosition();

	bool checkCollision(collision other);
	bool circleCollision(collision other);

	collisionType colType;

private:
	float width, height;
	float radius;
	float xRadius, yRadius;
	vector position;

};

void collision::setHeight(float h)
{
	height = h;
}

void collision::setWidth(float w)
{
	width = w;
}

void collision::setRadius(float r)
{
	radius = r;
}

bool collision::checkCollision(collision c2)
{
	switch (c2.colType)
	{
	case (circle) :
		break;
	case(rectangle):
	case (point) :
		break;
	default:
		break;
	}
}

bool collision::circleCollision(collision c2)
{
	float colDist = radius + c2.getRadius();
	float distBetween = vector::distance(c2.getPosition());
}

collision::collision()
{
}

collision::~collision()
{
}