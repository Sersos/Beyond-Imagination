#pragma once
#include "Vector3.h"
class ScaleManager
{
public:
	ScaleManager(Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	~ScaleManager();

	float x;
	float y;
	float z;
};

