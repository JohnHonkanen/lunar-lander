#include <cmath>

class vector
{
public:
	vector(float, float);
	vector(float, float, float);
	vector();
	~vector();
	void setX(float);
	void setY(float);
	float getX();
	float getY();

	void setZ(float);
	float getZ();

	void setAngle(float);
	float getAngle();

	float getLength();
	void setLength(float);

	vector normalize();
	vector cross(vector);

	vector add(vector);
	vector subtract(vector);
	vector multiply(float);
	vector divide(float);

	void addTo(vector);
	void subtractBy(vector);
	void multiplyBy(float);
	void divideBy(float);

	float distance(vector v2);

private:
	float _x, _y, _z;
};