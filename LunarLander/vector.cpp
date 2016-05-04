#include "vector.h"

/*
	Constructor
*/
vector::vector()
{

}
/*
	Constructor 2D
	@param x	X coordinate
	@param y	Y coordinate
*/
vector::vector(float x, float y)
{
	_x = x;
	_y = y;
	_z = 0;
}
/*
	Constructor 3D
	@param x	X coordinate
	@param y	Y coordinate
	@param z	Z coordinate
*/
vector::vector(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}
/*
	Set X value for Vector
	@param x	X coordinate
*/
void vector::setX(float x)
{
	_x = x;
}
/*
	Set Z value for Vector
	@param z	Z coordinate
*/
void vector::setZ(float z)
{
	_z = z;
}
/*
	Set Y value for Vector
	@param y	Y coordinate
*/
void vector::setY(float y)
{
	_y = y;
}
/*
	Get X Coordinate value
	@return X coordinate
*/
float vector::getX()
{
	return _x;
}
/*
	Get Y Coordinate value
	@return XY coordinate
*/
float vector::getY()
{
	return _y;
}
/*
	Get Z Coordinate value
	@return Z coordinate
*/
float vector::getZ()
{
	return _z;
}
/*
	Get Magnitude of Vector
	@return	Magnitude/Length
*/
float vector::getLength()
{
	return sqrt(_x * _x + _y * _y);
}
/*
	Set Magnitude of Vector
	@param length	Magnitide of Vector
*/
void vector::setLength(float length)
{
	float angle = getAngle();
	_x = cos(angle) * length;
	_y = sin(angle) * length;
}
/*
	Get Angle of Vector
	@return	Angle
*/
float vector::getAngle()
{
	return atan2(_y, _x);
}
/*
	Set Angle of Vector
	@param angle Angle of Vector
*/
void vector::setAngle(float angle)
{
	float length = getLength();
	_x = sin(angle) * length;
	_y = cos(angle) * length;
}
/*
	Normalize our vector to 1 Unit
	@return Normalized Vector
*/
vector vector::normalize()
{
	float length = getLength();
	float x = _x / length;
	float y = _y / length;

	return vector(x, y);
}
/*
	Cross Product of Two Vectors
	@param v2	Vector
	@return		Crossed Product Vector
*/
vector vector::cross(vector v2)
{
	float x = _y*v2.getZ() - _z*v2.getY();
	float y = _z*v2.getX() - _x*v2.getZ();
	float z = _x*v2.getY() - _y*v2.getX();

	return vector(x, y, z);
}

/*
	Add two Vectors together
	@param v2	Vector
	@return		New Added Vector
*/
vector vector::add(vector v2)
{
	return vector(_x + v2.getX(), _y + v2.getY());
}
/*
	Subtract two Vectors
	@param v2	Vector
	@return		New Subtracted Vector
*/
vector vector::subtract(vector v2)
{
	return vector(_x - v2.getX(), _y - v2.getY());
}
/*
	Multiply a Vector by Scalar Value
	@param val	Scalar Multiplication Value
	@return		New Scalar Multiplied Vector
*/
vector vector::multiply(float val)
{
	return vector(_x * val, _y * val);
}
/*
	Divide a Vector by a Scalar Value
	@param val	Scalar Division Value
	@return		New Scalar Division Vector
*/
vector vector::divide(float val)
{
	return vector(_x / val, _y / val);
}
/*
	Add a Vectors to this vector
	@param v2	Vector
*/
void vector::addTo(vector v2)
{
	_x += v2.getX();
	_y += v2.getY();
}
/*
	Subtract a Vector to this vector
	@param v2	Vector
*/
void vector::subtractBy(vector v2)
{
	_x -= v2.getX();
	_y -= v2.getY();
}
/*
	Multiply Scalar to this vector
	@param v2	Vector
*/
void vector::multiplyBy(float val)
{
	_x *= val;
	_y *= val;
}
/*
	Divide Scalar to this vector
	@param v2	Vector
*/
void vector::divideBy(float val)
{
	_x /= val;
	_y /= val;
}

/*
	Calculate Distance to a Vector
	@param v2	Vector
	@return Distance to Vector
*/
float vector::distance(vector v2)
{
	float dx = getX() - v2.getX();
	float dy = getY() - v2.getY();

	return abs(sqrt(dx*dx + dy*dy));
}

vector::~vector()
{
}

