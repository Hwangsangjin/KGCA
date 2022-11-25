struct VS_INPUT
{
	float4 position : POSITION;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.position = input.position;

	return output;
}

[maxvertexcount(9)]	// ���� ���̴����� ������� �ִ� ������ ���� ����
void GS(triangle VS_OUTPUT input[3], inout TriangleStream<VS_OUTPUT> triangle_stream)
{
	VS_OUTPUT output;

	// ���̽��� ����
	float3 center_position = (input[0].position.xyz + input[1].position.xyz + input[2].position.xyz) / 3.0f;

	// ���� �� ���� ������ ����Ͽ� ���̽� �߰�
	for (int i = 0; i < 3; i++)
	{
		output.position = input[i].position;
		triangle_stream.Append(output);

		int next = (i + 1) % 3;
		output.position = input[next].position;
		triangle_stream.Append(output);

		output.position = float4(center_position, 1.0f);
		triangle_stream.Append(output);
	}

	triangle_stream.RestartStrip();
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	return float4(1.0f, 1.0f, 0.0f, 1.0f);
}
