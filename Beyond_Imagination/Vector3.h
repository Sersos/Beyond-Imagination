#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:	
	Vector3(float x, float y, float z);

	//constructor for point with z = 0
	Vector3(float x, float y, float z = 0);

	//Get Length of 3 dimensional vector
	float length();

	float x;
	float y;
	float z;
};

#endif