float4 main( float3 Pos : POSITION ) : SV_POSITION
{
	return float4(Pos, 1.0f);
}