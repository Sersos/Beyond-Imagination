#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include "DirectxManager.h"
#include "Object.h"

class WorldObject : public Object
{
public:
	WorldObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	D3DXVECTOR3& position, D3DXVECTOR3& rotation, D3DXVECTOR3& scale);

	void update(float delta);
	virtual void render(ID3D11DeviceContext* deviceContext, D3DXMATRIX& view, D3DXMATRIX& projection) = 0;
	virtual void destroy() = 0;

	void updatePosition(D3DXVECTOR3& offset);
	void updateRotation(D3DXVECTOR3& rotation);
	void updateScale(D3DXVECTOR3& scale);

private:
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;
	D3DXMATRIX worldMatrix;
	D3DXMATRIX translationMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX scalingMatrix;
	
};

#endif





