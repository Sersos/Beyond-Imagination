#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H

struct PositionManager
{
	float x;
	float y;
	float z;
};

struct GlobalPosition : public PositionManager { };
struct LocalPosition : public PositionManager { };

#endif