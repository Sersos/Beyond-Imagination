#include <windows.h>
#include <windowsx.h>

#include "DirectxManager.h"
#include "Object.h"
#include "ShaderManager.h"
#include "Camera.h"



LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

DirectxManager* directxManager = NULL;
Object* object = NULL;
ShaderManager* shaderManager = NULL;
Camera* camera = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND window;
	WNDCLASSEX windowClass;

	directxManager = new DirectxManager();
	shaderManager = new ShaderManager();
	object = new Object();
	camera = new Camera();

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
	MSG msg;

	//GameManager initialize here
	directxManager->initialize(window);	
	camera->initialize(D3DXVECTOR3(2.0f, 2.0f, 5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	shaderManager->initialize(directxManager->getDevice(), directxManager->getDeviceContext(), object->getWorldMatrix(), 
							camera->getViewMatrix(), camera->getProjectionMatrix());
	object->initialize(directxManager->getDevice(), directxManager->getDeviceContext());

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}

		//GameManager render here
		directxManager->beginScene();		
		shaderManager->render(directxManager->getDeviceContext(), object);

		directxManager->presentScene();

	}

	//GameManager close here
	directxManager->close();
	shaderManager->close();

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