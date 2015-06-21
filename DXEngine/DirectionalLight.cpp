#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Camera.h"
#include "Director.h"
#include "Scene.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const D3DXCOLOR& color, const D3DXVECTOR3& dir)
{
	ZeroMemory(&m_d3dlight, sizeof(m_d3dlight));
	m_d3dlight.Type = D3DLIGHT_DIRECTIONAL;
	m_d3dlight.Diffuse = color;
	m_d3dlight.Specular = color * 0.1F;
	m_d3dlight.Ambient = color * 0.25F;
	m_d3dlight.Direction = dir;
}

DirectionalLight::~DirectionalLight()
{

}

void DirectionalLight::SetLightRenderState()
{
	theDevice->SetRenderState(D3DRS_LIGHTING, true);
	theDevice->SetLight(0, &m_d3dlight);
	theDevice->LightEnable(0, true);
}
