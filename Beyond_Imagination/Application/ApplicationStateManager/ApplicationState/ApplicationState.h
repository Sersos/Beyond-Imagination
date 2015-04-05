#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H

#include "DirectxManager.h"

class InputManager;

class ApplicationState
{
public:
	ApplicationState() { };

	virtual void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext) = 0;
	virtual void update() = 0;
	virtual void render(ID3D11DeviceContext* deviceContext) = 0;
	virtual void close() = 0;

protected:
	//protected variables here
	InputManager* m_inputManager;
	
};

#endif