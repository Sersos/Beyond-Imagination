#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	inputLayout = 0;
	vertexShader = 0;
	pixelShader = 0;
}

void ShaderManager::initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, uint16 id)
{
	useShader(deviceContext, id);
}

void ShaderManager::compileShaderFromFile(WCHAR* filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D10Blob* blobout)
{
	HRESULT hr;

	ID3D10Blob* error;
	//hr = D3DX10CompileFromFile();

	if (FAILED(hr))
		error->Release();
}

void ShaderManager::useShader(ID3D11DeviceContext* deviceContext, uint16 id)
{
	
	
	switch (id)
	{
		case SHADER_POSITION_COLOR:
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
		}

		case SHADER_POSITION_NORMAL:
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
		}		
	}

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
}
