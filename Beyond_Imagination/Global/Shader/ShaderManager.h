#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "DirectxManager.h"
#include "Global.h"

struct ConstantBuffer
{
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};

enum ShaderTypes
{
	SHADER_POSITION_COLOR,
	SHADER_POSITION_TEXTURE_NORMAL, //terrain, player for example
};

class ShaderManager
{
public:
	ShaderManager();	

	void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, uint16 id);
	void useShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, uint16 id);	
	void render(ID3D11DeviceContext* deviceContext, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection);
	void close();	

private:
	void compileShaderFromFile(WCHAR* filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D10Blob** blobout);

	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;
	ID3D11Buffer* matrixBuffer;

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};

#endif
