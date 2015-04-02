#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H

#include "DirectxManager.h"

class InputManager;

enum ApplicationStateType
{
	APPLICATION_MENU = 0,

	//states for singleplayer
	APPLICATION_SINGLEPLAYER_WHATEVER = 1,
	APPLICATION_SINGLEPLAYER_WHATEVER = 2,
	APPLICATION_SINGLEPLAYER_WHATEVER = 3,
	APPLICATION_SINGLEPLAYER_WHATEVER = 4,

	//later: status for multiplayer
	APPLICATION_MULTIPLAYER_MENU = 5, 
};

class ApplicationState
{
public:
	ApplicationState();

	virtual void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext) = 0;
	virtual void update() = 0;
	virtual void render(ID3D11DeviceContext* deviceContext) = 0;

protected:
	//protected variables here
	InputManager* m_inputManager;
};

#endif