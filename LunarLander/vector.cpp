#include "vector.h"

vector::vector()
{

}
vector::vector(float x, float y)
{
	_x = x;
	_y = y;
	_z = 0;
}

vector::vector(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

void vector::setX(float x)
{
	_x = x;
}

void vector::setZ(float z)
{
	_z = z;
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

float vector::getZ()
{
	return _z;
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

vector vector::normalize()
{
	float length = getLength();
	float x = _x / length;
	float y = _y / length;

	return vector(x, y);
}

vector vector::cross(vector v2)
{
	float x = _y*v2.getZ() - _z*v2.getY();
	float y = _z*v2.getX() - _x*v2.getZ();
	float z = _x*v2.getY() - _y*v2.getX();

	return vector(x, y, z);
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