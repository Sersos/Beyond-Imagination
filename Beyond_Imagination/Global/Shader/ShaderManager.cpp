#include "ShaderManager.h"
#include "Object.h"
#include <fstream>
#include <vector>

ShaderManager::ShaderManager() 
{
	inputLayout = NULL;	
	effect = NULL;
	effectTechnique = NULL;	
}

void ShaderManager::initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	HRESULT result;
	ID3D10Blob* compiledShader;	
	
	/*
	result = D3DX11CompileFromFile(L"Shader.fx", 0, 0, 0, "fx_5_0", 0, 0, 0, &compiledShader, NULL, 0);
	if (FAILED(result))
		MessageBox(0, L"Cant compile Shader", 0, MB_OK);*/
	
	std::ifstream fin("Shader.fxo", std::ios::binary);
	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> vectorShader(size);

	fin.read(&vectorShader[0], size);
	fin.close();


	result = D3DX11CreateEffectFromMemory(&vectorShader[0], size, 0, device, &effect);
	if (FAILED(result))
		MessageBox(0, L"Cant create Effect", 0, MB_OK);

	//can be released here
	//compiledShader->Release();

	effectTechnique = effect->GetTechniqueByName("PositionColor");
	effectWorldViewProjection = effect->GetVariableByName("worldViewProjection")->AsMatrix();
	
	buildInputLayout(device);

	deviceContext->IASetInputLayout(inputLayout);
}

void ShaderManager::render(ID3D11DeviceContext* deviceContext)
{
	
}

void ShaderManager::buildInputLayout(ID3D11Device* device)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0, 12,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	D3DX11_PASS_DESC passDesc;
	effectTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
	device->CreateInputLayout(layout, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &inputLayout);
}

void ShaderManager::close()
{
	// release inputlayout
	if (inputLayout)
		inputLayout->Release();

	//release effect
	if (effect)
		effect->Release();	
}

