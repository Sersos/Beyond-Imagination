#include "Camera.h"
#include "InputManager.h"

Camera::Camera(HWND* window)
{
	//initialize inputManager here
	m_inputManager = NULL;
	m_inputManager = new InputManager(window);	
}

void Camera::initialize(D3DXVECTOR3& position)
{
	//initialize up-Vector
	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;

	m_position = position;

	m_target = D3DXVECTOR3(0,0,0);

	selectPerspective(0);
}
void Camera::selectPerspective(int t)
{
	//Perspective Cam
	if (t == 0)
	{
		D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, 0.25f * D3DX_PI /* default*/,
			((float)DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT),
			1.0f,
			DEFAULT_VIEW_RANGE);
	}
	//Orthographic
	else if (t == 1)
	{
		D3DXMatrixOrthoLH(&m_projectionMatrix,2,(2/((float)DEFAULT_WINDOW_WIDTH/DEFAULT_WINDOW_HEIGHT)),1.0f,DEFAULT_VIEW_RANGE);
	}
}
void Camera::update()
{
	//get position before mouse is eventuell klicked
	D3DXVECTOR2 lastMousePosition = m_inputManager->getMousePosition();

	//get length of position vector
	float length = D3DXVec3Length(&m_position);

	m_forward = m_target - m_position;
	D3DXVec3Normalize(&m_forward, &m_forward);

	if (m_inputManager->isKeyPressed(MOUSE_RIGHT))
	{
		//get new mouse position after click
		D3DXVECTOR2 currentMousePosition = m_inputManager->getMousePosition();
				
		//mouse moved to the right
		if (currentMousePosition.x >= lastMousePosition.x)
		{
			//view have to rotate to the right
			D3DXMATRIX rotation;			
			D3DXMatrixRotationZ(&rotation, 0.5f);
			D3DXVec3Transform(&D3DXVECTOR4(m_target, 1.0f), &m_target, &rotation);

		}
		
		
	}
	
		//have to change to user specific keys

		//move forward
	if (m_inputManager->isKeyPressed(KEYBOARD_W))
	{
		m_position += -m_forward * CAMERA_MOVEMENT_SPEED;
		m_target += -m_forward * CAMERA_MOVEMENT_SPEED;
	}
	if (m_inputManager->isKeyPressed(KEYBOARD_S))
	{
		m_position += m_forward * CAMERA_MOVEMENT_SPEED;
		m_target += m_forward * CAMERA_MOVEMENT_SPEED;
	}

	if (m_inputManager->isKeyPressed(KEYBOARD_A))
	{
		D3DXVECTOR3 crossProduct = *D3DXVec3Cross(&m_forward, &m_forward, &m_up);
		m_position += *D3DXVec3Normalize(&m_right, &crossProduct) * CAMERA_MOVEMENT_SPEED;
		m_target += *D3DXVec3Normalize(&m_right, &crossProduct) * CAMERA_MOVEMENT_SPEED;
	}

	if (m_inputManager->isKeyPressed(KEYBOARD_D))
	{
		D3DXVECTOR3 crossProduct = *D3DXVec3Cross(&m_forward, &m_forward, &m_up);
		m_position += -(*D3DXVec3Normalize(&m_right, &crossProduct) * CAMERA_MOVEMENT_SPEED);
		m_target += -(*D3DXVec3Normalize(&m_right, &crossProduct) * CAMERA_MOVEMENT_SPEED);
	}

	//get current view matrix after updates	
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_target, &m_up);
}

D3DXMATRIX Camera::getViewMatrix()
{
	return m_viewMatrix;
}

D3DXMATRIX Camera::getProjectionMatrix()
{
	return m_projectionMatrix;
}

//private functions
void Camera::move(D3DXVECTOR3& offset)
{
	m_position.x += offset.x;
	m_position.y += offset.y;
	m_position.z += offset.z;

	m_target.x += offset.x;
	m_target.y += offset.y;
	m_target.z += offset.z;
}