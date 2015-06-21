
matrix matWorldViewProj;

void VS(in float3 pos : POSITION,
	in float3 normal : NORMAL,
	out float4 oPos : POSITION,
	out float4 color : COLOR)
{
	// Output the position
	oPos = mul(float4(pos, 1.f), matWorldViewProj);
	float s = dot(normal, normalize(float3(-1.0f, 1.0f, -1.0f)));
	if (s < 0.0f)
		s = 0.0f;
	
	color = float4(s, s, s, 0);
}

void PS(in float4 color : COLOR,
	out float4 oColor : COLOR)
{
	oColor = color;
}

technique Teapot
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}