#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include "PositionManager.h"
#include "RotationManager.h"
#include "ScaleManager.h"
#include "Vector3.h"
#include "DirectxManager.h"
#include "Object.h"

class WorldObject : public Object
{
public:
	WorldObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
				Vector3& position, Vector3& rotation, Vector3& scale);

	virtual void update(float delta) = 0;
	virtual void render(ID3D11DeviceContext* deviceContext, D3DXMATRIX& view, D3DXMATRIX& projection) = 0;
	virtual void destroy() = 0;

	void updatePosition(Vector3& offset);
	void updateRotation(Vector3& rotation);
	void updateScale(Vector3& scale);

private:
	GlobalPosition position;
	GlobalRotation rotation;
	GlobalScale scale;

	D3DXMATRIX worldMatrix;

	bool active;
	
};

#endif





