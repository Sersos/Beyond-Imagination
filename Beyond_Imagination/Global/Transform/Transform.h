#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "DirectxManager.h"

class Transform
{
public:
	static D3DXMATRIX translate(D3DXMATRIX* world, D3DXVECTOR3& offset)
	{
		return *D3DXMatrixTranslation(world, offset.x, offset.y, offset.z);
	}

	static D3DXMATRIX rotate(D3DXMATRIX* world, D3DXVECTOR3& rotation)
	{
		return *D3DXMatrixRotationYawPitchRoll(world, rotation.x, rotation.y, rotation.z);
	}

	static D3DXMATRIX scale(D3DXMATRIX* world, D3DXVECTOR3& scale)
	{
		return *D3DXMatrixScaling(world, scale.x, scale.y, scale.z);
	}
};

#endif