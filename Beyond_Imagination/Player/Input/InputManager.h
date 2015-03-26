#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <Windows.h>
#include <windowsx.h>
#include <DirectxManager.h>

enum MouseOpcodes
{
	//mouse codes
	MOUSE_LEFT_KEY	= 0x01,
	MOUSE_RIGHT_KEY = 0x02,

};

enum KeyboardOpcodes
{
	//not finished
	KEYBOARD_W = 1,
	KEYBOARD_S = 2,
};

class InputManager
{
public:
	InputManager(HWND* window /* windows window */);

	//method to update mouse position and check if mouse is in window already
	void update();

	//true if key of button id is pressed, else false
	bool isKeyPressed(int button);

	// return 2Vector with MousePosition in window
	D3DXVECTOR2 getMousePosition();	

private:
	//true if mouse is in window and window is active
	bool isCursorInWindow();

	//get status of specific button
	bool getKeyState(int button);

	HWND* window;
	POINT cursorPosition;
	
};


#endif