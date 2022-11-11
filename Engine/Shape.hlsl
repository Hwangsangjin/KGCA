Texture2D baseTexture : register(t0);
SamplerState baseSampler : register(s0);

cbuffer CB_DATA : register(b0)
{
	matrix world : packoffset(c0);
	matrix view : packoffset(c4);
	matrix projection : packoffset(c8);
};

struct VS_INPUT
{
	float4 position : POSITION;
	float4 normal : NORMAL;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 normal : NORMAL;
	float4 color : COLOR0;
	float2 uv : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT) 0;
	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	output.normal = input.normal;
	output.color = input.color;
	output.uv = input.uv;

	return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	return input.color;
}
