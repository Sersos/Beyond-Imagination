#include "Camera.h"
#include "InputManager.h"


Camera::Camera(HWND* window)
{
	//initialize inputManager here
	m_inputManager = NULL;
	m_inputManager = new InputManager(window);	
}

void Camera::initialize(D3DXVECTOR3 position)
{
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_position = position;
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 90.0f);
	m_target = D3DXVECTOR3(0,0,1);
	m_forward = m_target - m_position;
	
	//        Bogenmaﬂ                PI/180
	m_YawPitchRoll = m_rotation * 0.0174532925f;
	D3DXMatrixRotationYawPitchRoll(&m_rotationMatrix, m_YawPitchRoll.x, m_YawPitchRoll.y, m_YawPitchRoll.z);

	//set target und up vector with rotationmatrix
	D3DXVec3TransformCoord(&m_target, &m_target, &m_rotationMatrix);
	D3DXVec3TransformCoord(&m_up, &m_up, &m_rotationMatrix);
	
	m_target = m_position + m_target;

	D3DXMatrixLookAtLH(&m_viewMatrix,&m_position,&m_target,&m_up);

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
	m_forward = m_target - m_position;
	D3DXVec3Normalize(&m_forward, &m_forward);
	controll();
	
	//get current view matrix after updates	
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_target, &m_up);
}

void Camera::controll()
{
	//target in this case everytime in front of the cam!
	m_target = D3DXVECTOR3(0, 0, 1);

	if (m_inputManager->isKeyPressed(KEYBOARD_W))
	{
		m_position += m_forward * CAMERA_MOVEMENT_SPEED;
	}
	if (m_inputManager->isKeyPressed(KEYBOARD_S))
	{
		m_position -= m_forward * CAMERA_MOVEMENT_SPEED;
	}

	if (m_inputManager->isKeyPressed(KEYBOARD_A))
	{
		D3DXVECTOR3 crossProduct = *D3DXVec3Cross(&m_forward, &m_forward, &m_up);
		m_position += *D3DXVec3Normalize(&m_right, &crossProduct) * CAMERA_MOVEMENT_SPEED;
	}

	if (m_inputManager->isKeyPressed(KEYBOARD_D))
	{
		D3DXVECTOR3 crossProduct = *D3DXVec3Cross(&m_forward, &m_forward, &m_up);
		m_position -= *D3DXVec3Normalize(&m_right, &crossProduct) * CAMERA_MOVEMENT_SPEED;
	}

	//Yaw
	if (m_inputManager->isKeyPressed(KEYBOARD_J))
	{
		m_rotation.y += 0.1f;
		
	}
	if (m_inputManager->isKeyPressed(KEYBOARD_L))
	{
		m_rotation.y -= 0.1f;
	}
	//Pitch
	if (m_inputManager->isKeyPressed(KEYBOARD_I))
	{
		m_rotation.x -= 0.1f;
	}
	if (m_inputManager->isKeyPressed(KEYBOARD_K))
	{
		m_rotation.x += 0.1f;
	}
	//Roll
	//_________________________________________DONT RUN____________________________________
	if (m_inputManager->isKeyPressed(KEYBOARD_U))
	{
		m_rotation.z -= 0.1f;
	}
	if (m_inputManager->isKeyPressed(KEYBOARD_O))
	{
		m_rotation.z += 0.1f;
	}
	//______________________________________________________________________________________


	//bogenmaﬂ
	m_YawPitchRoll = m_rotation * 0.0174532925f;
	D3DXMatrixRotationYawPitchRoll(&m_rotationMatrix, m_YawPitchRoll.x, m_YawPitchRoll.y, m_YawPitchRoll.z);

	//calaculate the target position with rotationmatrix!
	D3DXVec3TransformCoord(&m_target, &m_target, &m_rotationMatrix);
	
	m_target += m_position;
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