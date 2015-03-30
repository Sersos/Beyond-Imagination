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
	//initialize up-Vector
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	this->position = position;
	this->target = target;	

	D3DXMatrixLookAtLH(&viewMatrix, &this->position, &this->target, &up);
	camType(1);

}
void Camera::camType(int t)
{
	//Perspective Cam
	if (t == 0)
	{
		D3DXMatrixPerspectiveFovLH(&projectionMatrix, 0.25f * D3DX_PI /* default*/,
			((float)DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT),
			1.0f,
			DEFAULT_VIEW_RANGE);
	}
	//Orthographic
	else if (t == 1)
	{
		D3DXMatrixOrthoLH(&projectionMatrix,2,(2/((float)DEFAULT_WINDOW_WIDTH/DEFAULT_WINDOW_HEIGHT)),1.0f,DEFAULT_VIEW_RANGE);
	}
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