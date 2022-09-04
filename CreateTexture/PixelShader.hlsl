Texture2D objTexture : register(t0);
SamplerState objSamplerState : register(s0);

struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float2 texCoord : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	float3 pixelColor = objTexture.Sample(objSamplerState, input.texCoord);
	
	return float4(pixelColor, 1.0f);
}