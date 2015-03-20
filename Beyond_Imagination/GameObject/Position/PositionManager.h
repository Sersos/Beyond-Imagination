#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H

class PositionManager
{
public:
	PositionManager(Vector3 v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	float x;
	float y;
	float z;
}

#endif