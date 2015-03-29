#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "DirectxManager.h"
#include "Global.h"

class Object;

enum ShaderTypes
{
	SHADER_POSITION_COLOR,
	SHADER_POSITION_TEXTURE_NORMAL, //terrain, player for example
};

class ShaderManager
{
public:
	ShaderManager();	

	void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection);
	void update();
	void render(ID3D11DeviceContext* deviceContext);
	void close();	

	ID3DX11EffectTechnique* effectTechnique;
	ID3DX11EffectMatrixVariable* effectWorldViewProjection;	
	
	D3DXMATRIX g_worldViewProjection;

private:	
	void buildInputLayout(ID3D11Device* device);

	ID3D11InputLayout* inputLayout;
	ID3DX11Effect* effect;		
	
};

#endif
