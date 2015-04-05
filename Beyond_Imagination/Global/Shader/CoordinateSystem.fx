cbuffer cbPerObject
{
	float4x4 gWorldViewProjection;
};

struct VOut
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
};

VOut VShader(float3 position : POSITION, float4 color : COLOR)
{
	VOut output;

	output.Position = mul(float4(position, 1.0f), gWorldViewProjection);
	output.Color = color;

	return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	return color;
}


technique11 CoordinateSystem
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VShader()));
		SetPixelShader(CompileShader(ps_5_0, PShader()));
	}
};