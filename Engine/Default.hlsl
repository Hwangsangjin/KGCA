Texture2D baseTexture : register(t0);
Texture2D MaskTexture : register(t1);
SamplerState baseSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
	float2 uv : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT) 0;
	output.position = float4(input.position, 1.0f);
	output.color = input.color;
	output.uv = input.uv;
	
	return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 color = baseTexture.Sample(baseSampler, input.uv);
	return color;
}
