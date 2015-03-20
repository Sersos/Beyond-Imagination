#include "Vector3.h"
#include <math.h>

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::length()
{
	double temp = x * x + y * y + z * z;
	return sqrt(temp);
}


