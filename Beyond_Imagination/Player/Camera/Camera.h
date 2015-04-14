#ifndef CAMERA_H
#define CAMERA_H

#include "DirectxManager.h"
#include "Global.h"


class InputManager;

class Camera
{
public:
	Camera(HWND* window);	

	void initialize(D3DXVECTOR3 position);
	void update();
	void controll();

	//select Left hand or ortho perspective, 0 for left handed and 1 for ortho
	void selectPerspective(int t /* id */);
	
	D3DXMATRIX getViewMatrix();
	D3DXMATRIX getProjectionMatrix();	

	D3DXVECTOR3 m_forward;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_target;


	D3DXVECTOR3 setPosition(D3DXVECTOR3 position){ m_position=position; };
	D3DXVECTOR3 setRotation(D3DXVECTOR3 rotation){ m_rotation=rotation; };
	D3DXVECTOR3 getPosition(){ return m_position; };
	D3DXVECTOR3 getRotation(){ return m_rotation; };

private:
	void move(D3DXVECTOR3& offset);

	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_YawPitchRoll;

	D3DXMATRIX	m_positionMatrix;
	D3DXMATRIX	m_rotationMatrix;
	D3DXMATRIX	m_viewMatrix;
	D3DXMATRIX	m_projectionMatrix;

	InputManager* m_inputManager;
};

#endif