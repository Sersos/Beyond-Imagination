#include "Camera.h"
#include "InputManager.h"

Camera::Camera(HWND* window)
{
	//initialize inputManager here
	inputManager = NULL;
	inputManager = new InputManager(window);
}

void Camera::initialize(D3DXVECTOR3& position, D3DXVECTOR3& target)
{
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->position = position;
	this->target = target;	

	D3DXMatrixLookAtLH(&viewMatrix, &this->position, &this->target, &up);

	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 0.25f * D3DX_PI /* default*/,
		((float)DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT),
		1.0f,
		DEFAULT_VIEW_RANGE);
}

void Camera::update()
{
	D3DXVECTOR2 lastMousePosition = inputManager->getMousePosition();

	if (inputManager->isKeyPressed(MouseOpcodes::MOUSE_LEFT_KEY))
	{
	
		//if (lastPositioninputManager->getMousePosition() > )
	}
}

D3DXMATRIX Camera::getViewMatrix()
{
	return viewMatrix;
}

D3DXMATRIX Camera::getProjectionMatrix()
{
	return projectionMatrix;
}