#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "DirectxManager.h"
#include "Global.h"
#include "Material.h"
#include "LightManager.h"

class Camera;

enum ShaderTypes
{
	SHADER_POSITION_COLOR,
	SHADER_POSITION_NORMAL, 
};

class ShaderManager
{
public:
	ShaderManager();	

	void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void update();
	void render(ID3D11DeviceContext* deviceContext, Camera* camera);
	void close();	

	ID3DX11EffectTechnique* m_effectTechnique;

	ID3DX11EffectMatrixVariable* m_effectWorldViewProjection; //in object
	ID3DX11EffectMatrixVariable* m_effectWorld;	//in object
	ID3DX11EffectMatrixVariable* m_effectWorldInvTranspose; //in object

	//in shaderManager
	ID3DX11EffectVectorVariable* m_effectEyePosition;
	ID3DX11EffectVariable* m_effectDirectionalLight;
	ID3DX11EffectVariable* m_effectPointLight;
	ID3DX11EffectVariable* m_effectSpotLight;
	ID3DX11EffectVariable* m_effectMaterial;

	Material m_material;
	DirectionalLight m_directionalLight;
	PointLight m_pointLight;
	SpotLight m_spotLight;
	
	D3DXMATRIX m_worldViewProjection;

private:	
	void buildInputLayout(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	ID3D11InputLayout* m_inputLayout;
	ID3DX11Effect* m_effect;	
	
};

#endif
