#ifndef SINGLEPLAYERGAME_H
#define SINGLEPLAYERGAME_H

#include "ApplicationState.h"

class SinglePlayerGame : public ApplicationState
{
public:
	SinglePlayerGame();

	void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void update();
	void render(ID3D11DeviceContext* deviceContext);
	void close();

private:

	
};

#endif