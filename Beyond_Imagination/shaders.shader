cbuffer cbPerObject
{
	float4x4 worldViewProjection;
};

struct VOut
{
    float4 Position : SV_POSITION;
    float4 Color	: COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

	//mul = multiply
	output.Position = mul(position, worldViewProjection);
	
    output.Color = color;

    return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    return color;
}

technique11 C
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_5_0, VShader() ) );			
		SetPixelShader( CompileShader( ps_5_0, PShader()  ) );
	}
}