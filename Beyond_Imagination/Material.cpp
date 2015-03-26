#include "Material.h"


Material::Material(ID3D11Device* _device, WCHAR _effectFileName, std::string _techniqueName):
diffuseColor(1.0f, 1.0f, 1.0f, 1.0f), ambientColor(0.5f, 0.5f, 0.5f, 0.5f)
{
	//set Parameters
	device = _device;
	effectFileName = _effectFileName;
	techniqueName = _techniqueName;

	//pointers to Null
	deviceContext = NULL;
	effect = NULL;
	technique = NULL;
	materialAmbientColorVariable = NULL;
	materialDiffuseColorVariable = NULL;

}
//set all effekt variables
void Material::setup()
{
	if (materialAmbientColorVariable)
		materialAmbientColorVariable->SetFloatVector(ambientColor);
	if (materialDiffuseColorVariable)
		materialDiffuseColorVariable->SetFloatVector(diffuseColor);
}
//Loading shader and get Technique
void Material::create()
{
	//set Material parameters to the Effect
	materialAmbientColorVariable = effect->GetVariableByName("materialAmbientColor")->AsVector();
	materialDiffuseColorVariable = effect->GetVariableByName("materialDiffuseColor")->AsVector();
	
	device->GetImmediateContext(&deviceContext);

	DWORD shaderFlag = D3D10_SHADER_ENABLE_STRICTNESS;

	
	ID3DBlob* blob = NULL;

	compileShaderFromFile(&effectFileName, "", "fx_5_0", shaderFlag, &blob);
	D3DX11CreateEffectFromMemory(blob->GetBufferPointer(),blob->GetBufferSize(),shaderFlag,device,&effect);

	technique = effect->GetTechniqueByName(techniqueName.c_str());
}
//D3DX11CompileFromFile with less parameters
void Material::compileShaderFromFile(WCHAR* filename, LPCSTR entryPoint, LPCSTR shaderModel,DWORD flag, ID3D10Blob** blobout)
{
	D3DX11CompileFromFile(filename, NULL, NULL, entryPoint, shaderModel, flag, NULL, NULL, blobout, NULL, NULL);
}

void Material::createVertexLayout(const D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements, ID3D11InputLayout** inputLayout)
{
	D3DX11_PASS_DESC passDesc;
	technique->GetPassByIndex(0)->GetDesc(&passDesc);
	device->CreateInputLayout(layout, numElements,passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, inputLayout);
}
void Material::destroy()
{
	if (effect)
		effect->Release();
	if (deviceContext)
		deviceContext->Release();
}



void Material::setDiffuseColor(D3DXCOLOR c)
{
	diffuseColor = c;
}
void Material::setAmbientColor(D3DXCOLOR c)
{
	ambientColor = c;
}

ID3DX11Effect* Material::getEffect()
{
	return effect;
}
ID3DX11EffectTechnique* Material::getTechnique()
{
	return technique;
}
Material::~Material()
{
}
