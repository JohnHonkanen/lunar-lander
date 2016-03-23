class vector
{
public:
	vector(float, float);
	vector();
	~vector();
	void setX(float);
	void setY(float);
	float getX();
	float getY();

	void setAngle(float);
	float getAngle();

	float getLength();
	void setLength(float);

	vector add(vector);
	vector subtract(vector);
	vector multiply(float);
	vector divide(float);

	void addTo(vector);
	void subtractBy(vector);
	void multiplyBy(float);
	void divideBy(float);

private:
	float _x, _y;
};