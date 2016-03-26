#include "vector.h"

vector::vector()
{

}
vector::vector(float x, float y)
{
	_x = x;
	_y = y;
}

void vector::setX(float x)
{
	_x = x;
}

void vector::setY(float y)
{
	_y = y;
}

float vector::getX()
{
	return _x;
}

float vector::getY()
{
	return _y;
}

float vector::getLength()
{
	return sqrt(_x * _x + _y * _y);
}

void vector::setLength(float length)
{
	float angle = getAngle();
	_x = cos(angle) * length;
	_y = sin(angle) * length;
}

float vector::getAngle()
{
	return atan2(_y, _x);
}

void vector::setAngle(float angle)
{
	float length = getLength();
	_x = sin(angle) * length;
	_y = cos(angle) * length;
}

vector vector::add(vector v2)
{
	return vector(_x + v2.getX(), _y + v2.getY());
}

vector vector::subtract(vector v2)
{
	return vector(_x - v2.getX(), _y - v2.getY());
}

vector vector::multiply(float val)
{
	return vector(_x * val, _y * val);
}

vector vector::divide(float val)
{
	return vector(_x / val, _y / val);
}

void vector::addTo(vector v2)
{
	_x += v2.getX();
	_y += v2.getY();
}

void vector::subtractBy(vector v2)
{
	_x -= v2.getX();
	_y -= v2.getY();
}

void vector::multiplyBy(float val)
{
	_x *= val;
	_y *= val;
}

void vector::divideBy(float val)
{
	_x /= val;
	_y /= val;
}

vector::~vector()
{
}