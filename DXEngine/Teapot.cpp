#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Camera.h"
#include "Director.h"
#include "Scene.h"
#include "Teapot.h"

Teapot::Teapot()
{
	D3DXCreateTeapot(theDevice, &m_mesh, nullptr);
	
	ID3DXBuffer* errorBuffer;
	D3DXCreateEffectFromFile(theDevice, "Teapot.fx", 0, 0,
		D3DXSHADER_DEBUG, 0, &m_effect, &errorBuffer);

	if (errorBuffer)
	{
		Error((char*)errorBuffer->GetBufferPointer());
		errorBuffer->Release();
	}

	m_hWorldViewProj = m_effect->GetParameterByName(0, "matWorldViewProj");
}

Teapot::~Teapot()
{
	m_mesh->Release();
	m_mesh = nullptr;
	m_effect->Release();
	m_effect = nullptr;
}

void Teapot::Update()
{

}

void Teapot::Render()
{
	m_effect->SetMatrix(m_hWorldViewProj, &(theCamera->GetViewProjMatrix()));

	RenderWithEffect(m_effect, "Teapot", [&](){
		m_mesh->DrawSubset(0);
	});
	
}