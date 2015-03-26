
#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once
#include <d3d10_1.h>
#include <d3d10.h>
#include <D3DX10.h>
#include <D3D11.h>
#include <D3DX11.h>
#include <d3dx11effect.h>



#include <string>


class Material
{
protected:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	ID3DX11Effect* effect;
	WCHAR effectFileName;

	ID3DX11EffectTechnique* technique;
	std::string techniqueName;

	//Material variablen
	D3DXCOLOR diffuseColor;
	D3DXCOLOR ambientColor;

	ID3DX11EffectVectorVariable* materialDiffuseColorVariable;
	ID3DX11EffectVectorVariable* materialAmbientColorVariable;

public:
	Material(ID3D11Device* _device, WCHAR _effectFileName, std::string _techniqueName);

	virtual void setup();
	virtual void compileShaderFromFile(WCHAR* filename, LPCSTR entryPoint, LPCSTR shaderModel,DWORD flag, ID3D10Blob** blobout);
	virtual void create();
	virtual void destroy();
	virtual void createVertexLayout(const D3D11_INPUT_ELEMENT_DESC* pLayout,UINT numElements, ID3D11InputLayout** inputLayout);
	virtual void setDiffuseColor(D3DXCOLOR);
	virtual void setAmbientColor(D3DXCOLOR);
	ID3DX11Effect* getEffect();
	ID3DX11EffectTechnique* getTechnique();

	~Material();
};

#endif