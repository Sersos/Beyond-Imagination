#ifndef CAMERA_H
#define CAMERA_H

#include "DirectxManager.h"
#include "Global.h"

struct ConstantBuffer
{
	D3DXMATRIX view;
	D3DXMATRIX projection;
	D3DXMATRIX world;
};

class Camera
{
public:
	Camera();

	void initialize(D3DXVECTOR3& position, D3DXVECTOR3& target);
	void update();

	D3DXVECTOR3 getCameraPosition();
	D3DXMATRIX getViewMatrix();
	D3DXMATRIX getProjectionMatrix();

private:
	void rotateCamera(D3DXVECTOR3& offset);
	void moveCamera(D3DXVECTOR3& rotation);

	D3DXVECTOR3 position;
	D3DXVECTOR3 up;
	D3DXVECTOR3 target;

	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
};

#endif