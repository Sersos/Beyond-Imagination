#ifndef MATERIAL_H
#define MATERIAL_H

#include "DirectxManager.h"
#include <string>

struct Material
{
	D3DXVECTOR4 ambient;
	D3DXVECTOR4 diffuse;
	D3DXVECTOR4 specular;
	//D3DXVECTOR4 reflect; later
};

/*
class Material
{
public:
	//constructor with no parameters, better for create in other classes
	Material();

	virtual void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, LPCWSTR filename, LPCSTR effectName) { };


protected:
	ID3DX11Effect* m_effect;
	ID3DX11EffectTechnique* m_effectTechnique;		

	//Material variablen
	D3DXCOLOR m_diffuseColor;
	D3DXCOLOR m_ambientColor;

	//variables for shader
	ID3DX11EffectVectorVariable* m_DiffuseColor;
	ID3DX11EffectVectorVariable* m_AmbientColor;
	ID3DX11EffectVectorVariable* m_SpecularFactor;
	
	//WCHAR effectFileName;
public:
	
	
	virtual void setup();
	virtual void create(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	virtual void destroy();
	virtual void createVertexLayout(ID3D11Device* device, const D3D11_INPUT_ELEMENT_DESC* pLayout,UINT numElements, ID3D11InputLayout** inputLayout);
	virtual void setDiffuseColor(D3DXCOLOR);
	virtual void setAmbientColor(D3DXCOLOR);
	virtual void setupPerObject(const D3DXMATRIX& worldMatrix, const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projectionMatrix);
	virtual void setupPerFrame();

	ID3DX11Effect* getEffect();
	ID3DX11EffectTechnique* getTechnique();

	
};*/

#endif