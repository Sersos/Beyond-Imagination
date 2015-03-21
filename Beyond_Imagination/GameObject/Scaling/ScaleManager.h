#ifndef SCALEMANAGER_H
#define SCALEMANAGER_H

#include "Vector3.h"

struct ScaleManager
{
	float x;
	float y; 
	float z;
};

struct GlobalScale : public ScaleManager {};

#endif
