#include "ShaderManager.h"
#include "Object.h"
#include <fstream>
#include <vector>
#include "Camera.h"

ShaderManager::ShaderManager() 
{
	m_inputLayout = NULL;	
	m_effect = NULL;
	m_effectTechnique = NULL;	
}

void ShaderManager::initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	HRESULT result;
	
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

	result = D3DX11CreateEffectFromMemory(&vectorShader[0], size, 0, device, &m_effect);
	if (FAILED(result))
		MessageBox(0, L"Cant create Effect", 0, MB_OK);

	//select technique
	m_effectTechnique = m_effect->GetTechniqueByName("PositionColor");

	//cbPerObject
	m_effectWorld = m_effect->GetVariableByName("gWorld")->AsMatrix();
	m_effectWorldViewProjection = m_effect->GetVariableByName("gWorldViewProjection")->AsMatrix();
	m_effectWorldInvTranspose = m_effect->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	m_effectMaterial = m_effect->GetVariableByName("gMaterial");

	//cbPerFrame
	m_effectDirectionalLight = m_effect->GetVariableByName("gDirectionalLight");
	m_effectPointLight = m_effect->GetVariableByName("gPointLight");
	m_effectSpotLight = m_effect->GetVariableByName("gSpotLight");
	m_effectEyePosition = m_effect->GetVariableByName("gEyePosition")->AsVector();

	//initialize light here
	m_directionalLight.ambient = D3DXVECTOR4(0.2f, 0.5f, 0.2f, 1.0f);
	m_directionalLight.diffuse = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_directionalLight.specular = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_directionalLight.direction = D3DXVECTOR3(0, 0, -1);

	m_pointLight.ambient = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pointLight.diffuse = D3DXVECTOR4(0.7f, 0.7f, 0.7f, 1.0f);
	m_pointLight.specular = D3DXVECTOR4(0.7f, 0.7f, 0.7f, 1.0f);
	m_pointLight.att = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_pointLight.position = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_pointLight.range = 25.0f;

	m_spotLight.ambient = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	m_spotLight.diffuse = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);
	m_spotLight.specular = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_spotLight.att = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_spotLight.spot = 96.0f;
	m_spotLight.range = 10000.0f;

	//initialize material here
	m_material.ambient = D3DXVECTOR4(0.9f, 0.9f, 0.9f, 1.0f);
	m_material.diffuse = D3DXVECTOR4(0.48f, 0.77f, 0.46f, 1.0f);
	m_material.specular = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 16.0f);
	
	buildInputLayout(device, deviceContext);
}

void ShaderManager::render(ID3D11DeviceContext* deviceContext, Camera* camera)
{
	//cbPerObject
	m_effectMaterial->SetRawValue(&m_material, 0, sizeof(m_material));

	//cbPerFrame
	
	m_effectDirectionalLight->SetRawValue(&m_directionalLight, 0, sizeof(m_directionalLight));
	//m_effectPointLight->SetRawValue(&m_pointLight, 0, sizeof(m_pointLight));
	//m_effectSpotLight->SetRawValue(&m_spotLight, 0, sizeof(m_spotLight));
	m_effectEyePosition->SetRawValue(camera->getPosition(), 0, sizeof(camera->getPosition().x));	
}

void ShaderManager::buildInputLayout(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, 0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,  0, 12,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	D3DX11_PASS_DESC passDesc;
	m_effectTechnique->GetPassByIndex(0)->GetDesc(&passDesc);
	device->CreateInputLayout(layout, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_inputLayout);

	deviceContext->IASetInputLayout(m_inputLayout);
}

void ShaderManager::close()
{
	// release inputlayout
	if (m_inputLayout)
		m_inputLayout->Release();

	//release effect
	if (m_effect)
		m_effect->Release();	
}

