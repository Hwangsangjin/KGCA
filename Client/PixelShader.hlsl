// 픽셀 마다 호출된다.
// 해당 픽셀(SV_Target 레지스터에)의 컬러를 반환한다.
float4 main(float4 pos : SV_POSITION, float4 color : COLOR0) : SV_Target
{
	return color;
}