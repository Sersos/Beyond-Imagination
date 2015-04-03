#ifndef CAMERA_H
#define CAMERA_H

#include "DirectxManager.h"
#include "Global.h"

class InputManager;

class Camera
{
public:
	Camera(HWND* window);	

	void initialize(D3DXVECTOR3& position);
	void update();

	//select Left hand or ortho perspective, 0 for left handed and 1 for ortho
	void selectPerspective(int t /* id */);
	
	D3DXMATRIX getViewMatrix();
	D3DXMATRIX getProjectionMatrix();	

	D3DXVECTOR3 m_forward;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_target;
	D3DXVECTOR3 m_eulerAngle;

	D3DXVECTOR3 getPosition(){ return m_position; };

private:
	void move(D3DXVECTOR3& offset);

	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_position;
	

	D3DXMATRIX	m_viewMatrix;
	D3DXMATRIX	m_projectionMatrix;

	InputManager* m_inputManager;
};

#endif