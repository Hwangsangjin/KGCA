cbuffer CB_DATA : register(b0)
{
	float4 color : packoffset(c0);
	float time : packoffset(c1.w);
};

struct VS_INPUT
{
	float4 position : POSITION;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float3 position = input.position * time;
	output.position = float4(position, 1.0f);
	output.diffuse = color;
	
	return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	return input.diffuse;
}
