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

bool InputManager::isCursorInWindow()
{
	return ScreenToClient(*window, &cursorPosition);
}

D3DXVECTOR2 InputManager::getMousePosition()
{
	//return mousePosition x and y from POINT mousePosition
	return D3DXVECTOR2(cursorPosition.x, cursorPosition.y);
}
