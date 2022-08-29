// HLSL
// 정점 셰이더란 정점 버퍼에 있는 모든 정점을 1번씩 작업한다.(동차 좌표계)
// 정점 위치(SV_POSITION 레지스터)에는 반드시 float4로 반환해야 한다.
// POSITION(시멘틱 : 의미구조)
struct VS_INPUT
{
	float3 inPos : POSITION;
	float4 inColor : COLOR;
};

struct VS_OUTPUT
{
	float4 outPos : SV_POSITION;
	float4 outColor : COLOR0;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT) 0;
	output.outPos = float4(input.inPos, 1.0f);
	output.outColor = input.inColor;
	
	return output;
}