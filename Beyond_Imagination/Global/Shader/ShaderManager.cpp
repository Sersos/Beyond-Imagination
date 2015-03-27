#include "ShaderManager.h"
#include "Object.h"

ShaderManager::ShaderManager() : worldViewProjection(0)
{
	inputLayout = NULL;	
	effect = NULL;
	effectTechnique = NULL;	
}

void ShaderManager::initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection)
{
	_worldViewProjection = world * view * projection;

	HRESULT result;
	ID3D10Blob* compiledShader;

	result = D3DX11CompileFromFile(L"effect.fx", 0, 0, 0, "fx_5_0", 0, 0, 0, &compiledShader, NULL, 0);
	if (FAILED(result))
		MessageBox(0, L"Cant compile Shader", 0, MB_OK);

	result = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, device, &effect);
	if (FAILED(result))
		MessageBox(0, L"Cant create Effect", 0, MB_OK);

	//can be released here
	//compiledShader->Release();

	effectTechnique = effect->GetTechniqueByName("RenderScene");
	worldViewProjection = effect->GetVariableByName("worldViewProjection")->AsMatrix();

	buildInputLayout(device);	

	deviceContext->IASetInputLayout(inputLayout);
}

void ShaderManager::render(ID3D11DeviceContext* deviceContext, Object* object)
{
	worldViewProjection->SetMatrix(reinterpret_cast<float*>(&_worldViewProjection));

	D3DX11_TECHNIQUE_DESC techniqueDesc;
	effectTechnique->GetDesc(&techniqueDesc);
	
	for (UINT p = 0; p < techniqueDesc.Passes; ++p)
	{
		effectTechnique->GetPassByIndex(p)->Apply(0, deviceContext);
		object->render(deviceContext);
		deviceContext->DrawIndexed(36, 0, 0);
	}
}

void ShaderManager::buildInputLayout(ID3D11Device* device)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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

