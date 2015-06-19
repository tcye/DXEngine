#include "Stdafx.h"
#include "Core.h"


void RenderWithEffect(ID3DXEffect* effect, const char* tech, std::function<void()> func)
{
	D3DXHANDLE hTech = effect->GetTechniqueByName(tech);
	effect->SetTechnique(hTech);
	UINT numPasses = 0;
	effect->Begin(&numPasses, 0);
	for (auto i = 0u; i < numPasses; i++)
	{
		effect->BeginPass(i);

		func();

		effect->EndPass();
	}
	effect->End();
}