#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "DirectxManager.h"
#include "Global.h"

class Object;

struct ConstantBuffer
{
	//multiply world & view & projection matrix
	D3DXMATRIX worldViewProjection;
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

	void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection);
	void update();
	void render(ID3D11DeviceContext* deviceContext, Object* object);
	void close();	

private:	
	void buildInputLayout(ID3D11Device* device);

	ID3D11InputLayout* inputLayout;
	ID3DX11Effect* effect;
	ID3DX11EffectTechnique* effectTechnique;
	ID3DX11EffectMatrixVariable* worldViewProjection;

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};

#endif
