/*#pragma once
#include <D3D10.h>
#include <D3DX10.h>
#include <D3D11.h>
#include <D3DX11.h>
#pragma warning(disable : 4995) //deprecated warning
#include <string>
#pragma warning(default : 4995)

class Material
{
public:
	Material(ID3D11Device* device, std::string effectFileName, std::string techniqueName);
	virtual void Create();
	virtual void Destroy();
	virtual void CreateVertexLayout(const D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements, ID3D11InputLayout** inputLayout);
	
	~Material();

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	std::string techniqueName;
	std::string effectFileName;

	


};

