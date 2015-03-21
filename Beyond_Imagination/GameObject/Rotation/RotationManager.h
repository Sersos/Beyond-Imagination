#ifndef ROTATIONMANAGER_H
#define ROTATIONMANAGER_H

#include "Vector3.h"

struct RotationManager
{
	void Update()
	{
		rotationOverflow();
	}
	void rotationOverflow()
	{
		if (x >= 360 || x <= -360)		
			x = 0;
		
		if (y >= 360 || y <= -360)		
			y = 0;
			
		if (z >= 360 || z <= -360)		
			z = 0;		
	}

	float x;
	float y;
	float z;	
};

struct GlobalRotation : public RotationManager { };
struct LocalRotation : public RotationManager { };

#endif