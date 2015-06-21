
matrix matViewInv;
matrix matProj;

TextureCube texSky;

// Sampler, for sampling the skybox texture
sampler linear_sampler = sampler_state
{
    Texture   = (texSky);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = Clamp;
    ADDRESSV = Clamp;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
void VS ( in  float3 pos  : POSITION,
          out float4 oPos : POSITION,
          out float3 oTex  : TEXCOORD)
{
	float4x4 matViewInvNoTrans =
	{
		matViewInv[0],
		matViewInv[1],
		matViewInv[2],
		float4(0.f, 0.f, 0.f, 1.f)
	};
    // Output the position
	float4 texPos = mul(float4(pos, 1.0f), matViewInvNoTrans);
    oTex = texPos.xyz;

	oPos = mul(float4(pos, 1.0f), matProj);
}




//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
void PS( in  float3 tex : TEXCOORD,
         out float4 color : COLOR )
{
    // The skybox texture is pre-lit, so simply output the texture color
    color = texCUBE( linear_sampler, tex);
}





//--------------------------------------------------------------------------------------
// Default Technique
// Establishes Vertex and Pixel Shader
// Ensures base states are set to required values
// (Other techniques within the scene perturb these states)
//--------------------------------------------------------------------------------------
technique SkyBox
{
    pass P0
    {
        VertexShader = compile vs_2_0 VS();
        PixelShader  = compile ps_2_0 PS();
        
        ZEnable = FALSE;
        ZWriteEnable = FALSE;
        AlphaBlendEnable = FALSE;
        CullMode = CCW;
        AlphaTestEnable = FALSE;
    }
}

