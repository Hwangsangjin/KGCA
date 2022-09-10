struct VS_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT) 0;
	output.position = float4(input.position, 1.0f);
	output.color = input.color;
	
	return output;
}

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

struct PS_OUTPUT
{
	float4 color : SV_TARGET;
};

PS_OUTPUT PS(PS_INPUT input)
{
	PS_OUTPUT output;
	output.color = input.color;
	
	return output;
}
