#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "DirectxManager.h"
#include "ShaderManager.h"

struct Axis
{
	D3DXVECTOR3 Position;
	D3DXVECTOR4 Color;
};

class CoordinateSystem
{
public:
	CoordinateSystem();
	
	void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void update();
	void render(ID3D11DeviceContext* deviceContext, D3DXMATRIX view, D3DXMATRIX projection);
	void close();

private:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11InputLayout* m_inputLayout;

	D3DXMATRIX m_world;

	ID3DX11Effect* m_effect;
	ID3DX11EffectTechnique* m_effectTechnique;
	ID3DX11EffectMatrixVariable* m_effectWorldViewProjection;

};

#endif

