Texture2D base_texture : register(t0);
SamplerState base_sampler : register(s0);

struct VS_INPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.position = input.position;
	output.uv = input.uv;

	return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	return base_texture.Sample(base_sampler, input.uv);
}