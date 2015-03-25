#include "InputManager.h"

InputManager::InputManager(HWND* window)
{
	window = NULL;
	this->window = window;
}

void InputManager::update()
{
	if (isCursorInWindow())
		GetCursorPos(&cursorPosition);	
}

bool InputManager::isKeyPressed(int button)
{
	if (InputManager::getKeyState(button))
		return true;
	else
		return false;
}

bool InputManager::getKeyState(int button)
{
	if ((GetAsyncKeyState(button) & 0x8000) != 0)
		return true;
	else
		return false;
}

bool InputManager::isCursorInWindow()
{
	return ScreenToClient(*window, &cursorPosition);
}

D3DXVECTOR2 InputManager::getMousePosition()
{
	//return mousePosition x and y from POINT mousePosition
	return D3DXVECTOR2(cursorPosition.x, cursorPosition.y);
}
