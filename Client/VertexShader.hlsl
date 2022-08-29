// HLSL
// ���� ���̴��� ���� ���ۿ� �ִ� ��� ������ 1���� �۾��Ѵ�.(���� ��ǥ��)
// ���� ��ġ(SV_POSITION ��������)���� �ݵ�� float4�� ��ȯ�ؾ� �Ѵ�.
// POSITION(�ø�ƽ : �ṉ̀���)
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