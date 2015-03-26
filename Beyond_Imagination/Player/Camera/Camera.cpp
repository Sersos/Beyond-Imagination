#include "Camera.h"

Camera::Camera()
{

}

void Camera::initialize(D3DXVECTOR3& position, D3DXVECTOR3& target)
{
	this->position = position;
	this->target = target;

	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &this->position, &this->target, &up);	

	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 0.4f * 3.14f /* default*/,
		(float)DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT,
		0.1f,
		DEFAULT_VIEW_RANGE);
}

void Camera::update()
{

}

D3DXVECTOR3 Camera::getCameraPosition()
{
	return D3DXVECTOR3(position);
}

D3DXMATRIX Camera::getViewMatrix()
{
	return viewMatrix;
}

D3DXMATRIX Camera::getProjectionMatrix()
{
	return projectionMatrix;
}