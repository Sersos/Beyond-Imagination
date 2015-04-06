#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "DirectxManager.h"

class FileOutputManager;

class Transform
{
public:
	Transform(D3DXVECTOR3& position, D3DXVECTOR3& rotation, D3DXVECTOR3& scale);

	virtual D3DXMATRIX translate(D3DXVECTOR3& offset);
	virtual D3DXMATRIX rotate(D3DXMATRIX* world, D3DXVECTOR3& rotation);
	virtual D3DXMATRIX scale(D3DXMATRIX* world, D3DXVECTOR3& scale);

	D3DXVECTOR3 getPosition();
	D3DXVECTOR3 getRotation();

	D3DXMATRIX m_positionMatrix;
	
private:
	D3DXMATRIX m_world;


	D3DXMATRIX m_rotationMatrix;
	D3DXMATRIX m_scaleMatix;

	float* m_position_X;
	float* m_position_Y;
	float* m_position_Z;

	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_scale;

	Transform* m_parent;

	FileOutputManager* out;

};

#endif