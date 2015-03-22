// gameObject.cpp
#include "WorldObject.h"

WorldObject::WorldObject(ID3D11Device* device, ID3D11DeviceContext* deviceContext,
	D3DXVECTOR3& position, D3DXVECTOR3& rotation, D3DXVECTOR3& scale) 
{
	/*
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;

	this->rotation.x = rotation.x;
	this->rotation.y = rotation.y;
	this->rotation.z = rotation.z;

	this->scale.x = scale.x;
	this->scale.y = scale.y;
	this->scale.z = scale.z;	
	*/

	
	
}

void WorldObject::update(float delta)
{
	D3DXMATRIX translationMatrix;
	D3DXMatrixTranslation(&translationMatrix, position.x, position.y, position.z);

	D3DXMATRIX rotationX, rotationY, rotationZ, rotationMatrix;
	D3DXMatrixRotationX(&rotationX, rotation.x);
	D3DXMatrixRotationY(&rotationY, rotation.y);
	D3DXMatrixRotationZ(&rotationZ, rotation.z);
	rotationMatrix = rotationX * rotationY * rotationZ;
}

