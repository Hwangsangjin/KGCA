Texture2D baseTexture : register(t0);
SamplerState baseSampler : register(s0);

cbuffer CB_DATA : register(b0)
{
	matrix world : packoffset(c0);
	matrix view : packoffset(c4);
	matrix projection : packoffset(c8);
	float4 timer : packoffset(c12);
};

cbuffer CB_ANIMATION : register(b1)
{
	matrix bone[255];
}

struct VS_INPUT
{
	float4 position : POSITION;
	float4 normal : NORMAL;
	float4 color : COLOR;
	float2 uv : TEXCOORD;

	float4 index : INDEX;
	float4 weight : WEIGHT;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 normal : NORMAL;
	float4 color : COLOR0;
	float2 uv : TEXCOORD0;
	float4 lightColor : TEXCOORD1;
	float3 vLight : TEXCOORD2;
	float4 vWorld : TEXCOORD3;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 local = input.position;
	float4 anim = 0.0f;
	float4 animNormal = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		uint index = input.index[i];
		float weight = input.weight[i];
		anim += mul(local, bone[index]) * weight;
		animNormal += mul(input.normal, bone[index]) * weight;
	}

	output.position = mul(anim, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	output.normal = animNormal;
	output.color = input.color;
	output.uv = input.uv;

	float3 vLight = timer.xyz;
	output.vLight = vLight;
	float fDot = max(0.3f, dot(animNormal, -vLight));
	output.lightColor = float4(fDot, fDot, fDot, 1.0f);
	
	return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 color = baseTexture.Sample(baseSampler, input.uv);
	//return color * input.color * input.lightColor;
	return color;
}
