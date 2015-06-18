technique Teapot
{
	pass P0
	{
		LightType[0] = DIRECTIONAL;
		LightAmbient[0] = { 0.2f, 0.2f, 0.2f, 1.0f };
		LightDiffuse[0] = { 1.0f, 1.0f, 1.0f, 1.0f };
		LightSpecular[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
		LightDirection[0] = { 1.0f, -1.0f, 1.0f };

		LightPosition[0] = { 0.0f, 0.0f, 0.0f };
		LightFalloff[0] = 0.0f;
		LightRange[0] = 0.0f;
		LightTheta[0] = 0.0f;
		LightPhi[0] = 0.0f;
		LightAttenuation0[0] = 1.0f;
		LightAttenuation1[0] = 0.0f;
		LightAttenuation2[0] = 0.0f;
		LightEnable[0] = true;

		MaterialAmbient = { 1.0f, 1.0f, 1.0f, 1.0f };
		MaterialDiffuse = { 1.0f, 1.0f, 0.0f, 1.0f };
		MaterialSpecular = { 1.0f, 1.0f, 1.0f, 1.0f };
		MaterialEmissive = { 0.0f, 0.0f, 0.0f, 1.0f };
		MaterialPower = 8.0f;
	}
}