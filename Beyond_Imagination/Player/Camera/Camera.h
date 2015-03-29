#ifndef CAMERA_H
#define CAMERA_H

#include "DirectxManager.h"
#include "Global.h"

class InputManager;

class Camera
{
public:
	Camera(HWND* window);	

	void initialize(D3DXVECTOR3& position, D3DXVECTOR3& target);
	void update();
	
	D3DXMATRIX getViewMatrix();
	D3DXMATRIX getProjectionMatrix();

private:
	void rotateCamera(D3DXVECTOR3& offset);
	void moveCamera(D3DXVECTOR3& rotation);	

	D3DXVECTOR3 up;
	D3DXVECTOR3 position;
	D3DXVECTOR3 target;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;

	InputManager* inputManager;
};

#endif