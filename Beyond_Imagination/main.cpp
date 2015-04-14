#include <windows.h>
#include <windowsx.h>

#include "DirectxManager.h"
#include "Object.h"
#include "ShaderManager.h"
#include "Camera.h"
#include <string>
#include <sstream>
#include "InputManager.h"
#include "CoordinateSystem.h"
#include "Transform.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

DirectxManager* directxManager = NULL;
Object* object = NULL;
ShaderManager* shaderManager = NULL;
Camera* camera = NULL;
InputManager* inputManager = NULL;
CoordinateSystem* coordinateSystem = NULL;
Transform* trans = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND window;
	WNDCLASSEX windowClass;

	directxManager = new DirectxManager();
	shaderManager = new ShaderManager();
	object = new Object();	
	camera = new Camera(&window);
	inputManager = new InputManager(&window);
	coordinateSystem = new CoordinateSystem();
	trans = new Transform(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1));



	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW); //cursor style
	windowClass.lpszClassName = L"WindowClass";

	RegisterClassEx(&windowClass);

	RECT drawArea = { 0, 0, 1280, 720 }; //window size
	AdjustWindowRect(&drawArea, WS_OVERLAPPEDWINDOW, FALSE);

	window = CreateWindowEx(
		NULL,
		L"WindowClass",
		L"Beyond imagation", //window title
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		drawArea.right - drawArea.left,
		drawArea.bottom - drawArea.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(window, nCmdShow);

	std::wstring mMainWndCaption;
	MSG msg;

	//GameManager initialize here
	directxManager->initialize(window, true);	
	camera->initialize(D3DXVECTOR3(0, 0, 0));

	coordinateSystem->initialize(directxManager->getDevice(), directxManager->getDeviceContext());

	shaderManager->initialize(directxManager->getDevice(),
		directxManager->getDeviceContext());	
	object->initialize("models/Shockwave.obj", directxManager->getDevice(), directxManager->getDeviceContext());			
	
	//variables for fps counter
	unsigned long lastTime = GetTickCount();
	unsigned long timer = GetTickCount();
	double ms = 1000.0 / 60.0;
	double delta = 0;
	int updates = 0;
	int frames = 0;

	while (TRUE)
	{
		//GameManager render here
		inputManager->update();	
		camera->update();
		directxManager->beginScene();

		coordinateSystem->render(directxManager->getDeviceContext(), camera->getViewMatrix(), camera->getProjectionMatrix());

		shaderManager->render(directxManager->getDeviceContext(), camera);

		object->render(directxManager->getDeviceContext(),
				shaderManager,
				camera->getViewMatrix(),
				camera->getProjectionMatrix());			
		
		directxManager->presentScene();	

		long now = GetTickCount();
		delta += (now - lastTime) / ms;
		lastTime = now;
		while (delta >= 1)
		{
			updates++;
			delta--;

		}

		//update here		
		object->update();				

		frames++;

		if (GetTickCount() - timer > 1000)
		{
			timer += 1000;

			std::wostringstream outs;
			outs.precision(8);
			outs << mMainWndCaption << L" tx:" << camera->m_target.x <<
				L" ty:" << camera->m_target.y <<
				L" tz:" << camera->m_target.z <<
				 L" " << L"FPS: " << frames << L" " << L"UPS: " << updates << L" " <<
				L"MouseX: " << inputManager->getMousePosition().x << L" " << L"MouseY: " << inputManager->getMousePosition().y << L" ";
			SetWindowText(window, outs.str().c_str());

			updates = 0;
			frames = 0;
		}
		
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}

	}

	//GameManager close here
	directxManager->close();
	shaderManager->close();
	coordinateSystem->close();

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
			break;
		}

	return DefWindowProc(hWnd, message, wParam, lParam);
}