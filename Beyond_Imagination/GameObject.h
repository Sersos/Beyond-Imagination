
#include "Vector3.h"

class PositionManager;
class RotationManager;
class ScaleManager;

class GameObject
{
public:
	GameObject(Vector3& position, Vector3& rotation, Vector3& scale);

private:
	RotationManager* rotation;
	PositionManager* position;
	ScaleManager* scale;
	
};

