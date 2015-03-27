#include "Material.h"

Material::Material(ID3D11Device* device, WCHAR _effectFileName, CHAR _techniqueName) :
diffuseColor(1.0f, 1.0f, 1.0f, 1.0f), ambientColor(0.5f, 0.5f, 0.5f, 0.5f)
{
	//set Parameters	
	effectFileName = _effectFileName;
	techniqueName = _techniqueName;

	//pointers to Null	
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
//set Matrix von Effect
void Material::setupPerObject(const D3DXMATRIX& world, const D3DXMATRIX& view, const D3DXMATRIX& worldViewProjection)
{
	effect->GetVariableByName("world")->AsMatrix()->SetMatrix((float*)&world);
	effect->GetVariableByName("view")->AsMatrix()->SetMatrix((float*)&view);
	effect->GetVariableByName("worldViewProjection")->AsMatrix()->SetMatrix((float*)&worldViewProjection);
}
//set Light
void Material::setupPerFrame(/*const Light* light*/)
{
	D3DXVECTOR3 lightDir;
	D3DXVECTOR3 lightDiffuseColor;

	effect->GetVariableByName("lightDir")->AsVector()->SetFloatVector(lightDir);
	effect->GetVariableByName("lightDiffuse")->AsVector()->SetFloatVector(lightDiffuseColor);
	
}
//Loading shader and get Technique
void Material::create(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	
	device->GetImmediateContext(&deviceContext);

	//set Material parameters to the Effect
	materialAmbientColorVariable = effect->GetVariableByName("materialAmbientColor")->AsVector();
	materialDiffuseColorVariable = effect->GetVariableByName("materialDiffuseColor")->AsVector();

	// set effectfile path
	//WCHAR str[MAX_PATH] = L"Global\Effect\effect.fx";

	DWORD shaderFlag = D3D10_SHADER_ENABLE_STRICTNESS;
	
	ID3DBlob* blob = NULL;
	HRESULT result;

	result = D3DX11CompileFromFile(L"effect.fx", NULL, NULL, NULL, "fx_5_0", NULL, NULL, NULL, &blob, NULL, NULL);
	D3DX11CreateEffectFromMemory(blob->GetBufferPointer(),blob->GetBufferSize(),shaderFlag,device,&effect);

	technique = effect->GetTechniqueByName(techniqueName.c_str());
}

void Material::createVertexLayout(ID3D11Device* device, const D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements, ID3D11InputLayout** inputLayout)
{
	D3DX11_PASS_DESC passDesc;
	technique->GetPassByIndex(0)->GetDesc(&passDesc);
	device->CreateInputLayout(layout, numElements,passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, inputLayout);
}
void Material::destroy()
{
	if (effect)
		effect->Release();	
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
