#include "InputManager.h"

InputManager::InputManager(HWND* window)
{
	this->window = window;
}

void InputManager::update()
{
	GetCursorPos(&cursorPosition);

	GetWindowRect(*window, &windowRect);

	/*
	//jump 
	if (cursorPosition.x > windowRect.right)
	{
		setMousePosition(windowRect.left + 1, cursorPosition.y);
	}
	if (cursorPosition.y > windowRect.bottom)
	{
		setMousePosition(cursorPosition.x, windowRect.top + 1);
	}
	if (cursorPosition.x <= windowRect.left)
	{
		setMousePosition(windowRect.right-1, cursorPosition.y);
	}
	if (cursorPosition.y <= windowRect.top)
	{
		setMousePosition(cursorPosition.x, windowRect.bottom-1);
	}*/	
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

void InputManager::setMousePosition(int x, int y)
{
	SetCursorPos(x, y);

}
