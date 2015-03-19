#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector3.h"

class GlobalPosition;
class GlobalRotation;
class GlobalScale;

class GameObject
{
public:
	GameObject(Vector3& position, Vector3& rotation, Vector3& scale);

private:
	GlobalPosition* position;
	GlobalRotation* rotation;
	GlobalScale* scale;
	
};

#endif

