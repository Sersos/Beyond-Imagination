#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	
}

void ShaderManager::initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, uint16 id)
{
	compileShaderFromFile(L"shader_position_color.hlsl", "VS", "vs_5_0", &vsBlob);
	device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &vertexShader);
		
	compileShaderFromFile(L"shader_position_color.hlsl", "PS", "ps_5_0", &psBlob);
	device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &pixelShader);
	psBlob->Release();

	deviceContext->VSSetShader(vertexShader, 0, 0);
	deviceContext->PSSetShader(pixelShader, 0, 0);
	
	useShader(device, deviceContext, id);
}

void ShaderManager::compileShaderFromFile(WCHAR* filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D10Blob** blobout)
{
	D3DX10CompileFromFile(filename, NULL, NULL, entryPoint, shaderModel, NULL, NULL, NULL, blobout, NULL, NULL);	
}

void ShaderManager::useShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, uint16 id)
{
	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	
	device->CreateInputLayout(layout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
	deviceContext->IASetInputLayout(inputLayout);
}

void ShaderManager::close()
{
	if (inputLayout)
		inputLayout->Release();
	
	if (vertexShader)
		vertexShader->Release();

	if (pixelShader)
		pixelShader->Release();

	if (vsBlob)
		vsBlob->Release();
}
