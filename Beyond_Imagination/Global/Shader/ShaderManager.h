#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "DirectxManager.h"

class ShaderManager
{
	ShaderManager();
	~ShaderManager();

	void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	
	void close();	

private:
	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
};

#endif