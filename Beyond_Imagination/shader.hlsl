
struct cbPerObject
{
	float4x4 worldViewProjection;
};

struct Vertex_out
{
	float4 Position : SV_POSTION;
	float4 Color	: COLOR;
};

Vertex_out VShader(float4 position : POSITION, float4 color : COLOR)
{
	Vertex_out output;

	output.Position = mul(position, worldViewProjection);
	output.Color = color;

	return output;
}

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	return color;
}

technique11 PositionColor
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VShader()));
		SetPixelShader(CompileShader(ps_5_0, PShader()));
	};
}