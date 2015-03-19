#ifndef POSITION_H
#define POSITION_H
#include "Vector3.h"
class RotationManager
{
public:
	RotationManager(Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	
	void Update()
	{
		rotationOverflow();
	}
	void rotationOverflow()
	{
		if (x >= 360 || x <= -360)
		{
			x = 0;
		}
		if (y >= 360 || y <= -360)
		{
			y = 0;
		}	
		if (z >= 360 || z <= -360)
		{
			z = 0;
		}
	}
	float x;
	float y;
	float z;	
};

#endif