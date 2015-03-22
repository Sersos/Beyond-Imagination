struct VS_OUTPUT
{
	float3 Position : SV_POSTION;
	float4 Color : COLOR;
};

VS_OUTPUT VS(float3 Position : POSITION, float4 Color : COLOR)
{
	VS_OUTPUT output;

	output.Position = Position;
	output.Color = Color;

	return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	return input.Color;
}