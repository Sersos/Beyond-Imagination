#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "DirectxManager.h"
#include "Global.h"

enum ShaderTypes
{
	SHADER_POSITION_COLOR,
	SHADER_POSITION_NORMAL,
};

class ShaderManager
{
	ShaderManager();
	~ShaderManager();

	void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, uint16 id);
	void useShader(ID3D11DeviceContext* deviceContext, uint16 id);
	
	void close();	

private:
	void compileShaderFromFile(WCHAR* filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D10Blob* blobout);

	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
};

#endif