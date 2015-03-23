#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	vertexShader = NULL;
	pixelShader = NULL;
	inputLayout = NULL;
	matrixBuffer = NULL;
}

void ShaderManager::initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, uint16 id)
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	
	compileShaderFromFile(L"shaders.shader", "VShader", "vs_4_0", &vsBlob);
	compileShaderFromFile(L"shaders.shader", "PShader", "ps_4_0", &psBlob);
	
	device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &vertexShader);
	device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &pixelShader);	

	//create constant buffer desc
	ZeroMemory(&matrixBufferDesc, sizeof(D3D11_BUFFER_DESC));
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; //important
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	//finally, create buffer
	device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);

	//switch to render function
	deviceContext->VSSetShader(vertexShader, 0, 0);
	deviceContext->PSSetShader(pixelShader, 0, 0);

	useShader(device, deviceContext, id);
}

void ShaderManager::render(ID3D11DeviceContext* deviceContext, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ConstantBuffer* constantBuffer;

	D3DXMatrixTranspose(&this->world, &world);
	D3DXMatrixTranspose(&this->view, &view);
	D3DXMatrixTranspose(&this->projection, &projection);

	deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	constantBuffer = (ConstantBuffer*)mappedResource.pData;
	constantBuffer->world = this->world;
	constantBuffer->view = this->view;
	constantBuffer->projection = this->projection;
	deviceContext->Unmap(matrixBuffer, 0);

	// 0 position constant buffer in vertexShader, see b(0)
	deviceContext->VSSetConstantBuffers(0, 1, &matrixBuffer);	
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
	// release inputlayout
	if (inputLayout)
		inputLayout->Release();
	
	//release vertexShader
	if (vertexShader)
		vertexShader->Release();

	//release pixelShader
	if (pixelShader)
		pixelShader->Release();

	//release vsBlob
	if (vsBlob)
		vsBlob->Release();

	//release psBlob
	if (psBlob)
		psBlob->Release();

	//release constantBuffer
	if (matrixBuffer)
		matrixBuffer->Release();
}

void ShaderManager::compileShaderFromFile(WCHAR* filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D10Blob** blobout)
{
	D3DX11CompileFromFile(filename, NULL, NULL, entryPoint, shaderModel, NULL, NULL, NULL, blobout, NULL, NULL);
}
