#include <windows.h>
#include <windowsx.h>

#include "DirectxManager.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

DirectxManager* directxManager = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND window;
	WNDCLASSEX windowClass;

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
	directxManager = new DirectxManager();
	directxManager->initialize(window);
	directxManager->beginScene();

	while (TRUE)
	{
		//GameManager render here
		directxManager->beginScene();

		directxManager->presentScene();


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