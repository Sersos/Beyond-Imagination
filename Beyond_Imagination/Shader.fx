#include "LightHelper.fx"

cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldViewProjection;
	float4x4 gWorldInvTranspose;
	Material gMaterial;
};

cbuffer cbPerFrame
{
	DirectionalLight gDirectionalLight;
	PointLight gPointLight;
	SpotLight gSpotLight;
	float3 gEyePosition;
};

struct VertexIn
{
	float4 Position : POSITION;
	float3 Normal	: NORMAL;
};

struct VertexOut
{
    float4 Position		: SV_POSITION;
	float4 PositionIn	: POSITION; //dont know why
	float3 NormalIn		: NORMAL;
};

VertexOut VShader(VertexIn vertexIn)
{
    VertexOut output;
	
	//for pixelShader
	output.PositionIn = mul(vertexIn.Position, gWorld); 
	output.NormalIn = mul(vertexIn.Normal, (float3x3)gWorldInvTranspose);
	
	//multiply vertex position with worldViewProjection matrix
	output.Position = mul(vertexIn.Position, gWorldViewProjection);

    return output;
}

float4 PShader(VertexOut pixelIn) : SV_TARGET
{
	//normalize incoming normal vector
	pixelIn.NormalIn = normalize(pixelIn.NormalIn);

	float toEye = gEyePosition - pixelIn.PositionIn;

	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 a, d, s; //for ambient, diffuse and specular

	//for directionalLight
	computeDirectionalLight(gMaterial, gDirectionalLight, pixelIn.NormalIn, toEye, a, d, s);
	ambient += a;
	diffuse += d;
	specular += s;

	//for pointlight
	computePointLight(gMaterial, gPointLight, pixelIn.PositionIn, pixelIn.NormalIn, toEye, a, d, s);
	ambient += a;
	diffuse += d;
	specular += s;

	//for spotLight
	computeSpotLight(gMaterial, gSpotLight, pixelIn.PositionIn, pixelIn.NormalIn, toEye, a, d, s);
	ambient += a;
	diffuse += d;
	specular += s;

	float4 lightColor = ambient + diffuse + specular;

	lightColor.a = gMaterial.diffuse.a;

	return lightColor;
}

technique11 PositionColor
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_5_0, VShader() ) );			
		SetPixelShader( CompileShader( ps_5_0, PShader()  ) );
	}
}


