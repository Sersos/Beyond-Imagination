cbuffer cbPerObject
{
	matrix world;
	matrix view;
	matrix worldViewProjection;

	float4 materialAmbientColor;
	float4 materialDiffuseColor;
};
cbuffer cbPerFrame
{
	float3 lightDir;
	float time;
	float4 lightDiffuse;
};

Texture2D diffuseTexture;

SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};
 
struct VS_INPUT
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float2 TextureUV : TEXCOORD0;
};
struct VS_OUTPUT
{
	float4 Position : SV_POSITION;
	float4 Diffuse : COLOR0;
	float2 TextureUV : TEXCOORD0;
};

//VertexShader
VS_OUTPUT VShader(VS_INPUT i)
{
	VS_OUTPUT o;
	float3 normalWorldSpace;

	//From object space to world space
	o.Position = mul(i.Position, worldViewProjection);
	//normals form object space to world space
	normalWorldSpace = normalize(mul(i.Normal, (float3x3) world));

	//Calculate color with diffuse+ lightcolor depending on angle from light and the ambient Color
	o.Diffuse.rgb = materialDiffuseColor * lightDiffuse * max(0, dot(normalWorldSpace, lightDir)) + materialAmbientColor;
	o.Diffuse.a = 1.0f;


	o.TextureUV = i.TextureUV;

	return o;
}
//PixelShader 
float4 PShader(VS_OUTPUT o) : SV_TARGET
{
	//meshtexture modulated with diffuse
	return diffuseTexture.Sample(samLinear, o.TextureUV) * o.Diffuse;
}

//technique
technique11 RenderScene
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0,VShader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0,PShader()));
	}
}