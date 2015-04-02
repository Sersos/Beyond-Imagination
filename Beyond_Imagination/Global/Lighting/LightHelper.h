#ifndef LIGHTHELPER_H
#define LIGHTHELPER_H

#include "DirectxManager.h"

class LightHelper
{
public:
	static D3DXMATRIX inverseTranspose(D3DXMATRIX matrix)
	{
		D3DXMATRIX temp = matrix;
		temp._31 = 0.0f;
		temp._32 = 0.0f;
		temp._33 = 0.0f;
		temp._34 = 1.0f;

		float det = D3DXMatrixDeterminant(&temp);
		D3DXMATRIX inverse = *D3DXMatrixInverse(&temp, &det, &temp);
		return *D3DXMatrixTranspose(&temp, &inverse);
	}
};

#endif