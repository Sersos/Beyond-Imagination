#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <windows.h>
#include <windowsx.h>

class DirectxManager;

enum ApplicationStateType
{
	APPLICATION_MENU = 0,

	//states for singleplayer
	APPLICATION_SINGLEPLAYER_GAME = 1,
	APPLICATION_SINGLEPLAYER_MENU = 2,
	APPLICATION_SINGLEPLAYER_OPTIONS = 3,
	APPLICATION_SINGLEPLAYER_WHATEVER = 4,

	//later: status for multiplayer
	APPLICATION_MULTIPLAYER_MENU = 5,
};

class ApplicationState;
class SinglePlayerGame;

class ApplicationManager
{
public:
	ApplicationManager();

	void initialize(HWND* window);
	void update();
	void render();
	void close();

	void switchState(int newState);

private:
	int m_activeState;

	HWND* m_window;
	DirectxManager* m_directxManager;

	//gamestates here
	ApplicationState* m_applicationState[APPLICATION_MULTIPLAYER_MENU];
	SinglePlayerGame* m_singlePlayerGame;
};

#endif