#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Teapot.h"

Teapot::Teapot()
{
	D3DXCreateTeapot(theDevice, &m_mesh, nullptr);
	
	ID3DXBuffer* errorBuffer;
	auto hr = D3DXCreateEffectFromFile(
		theDevice,
		"Teapot.fx",
		0,
		0,
		D3DXSHADER_DEBUG,
		0,
		&m_effect,
		&errorBuffer);

	if (errorBuffer)
	{
		Error((char*)errorBuffer->GetBufferPointer());
		errorBuffer->Release();
	}
	if (FAILED(hr))
	{
		Error("D3DXCreateEffectFromFile() - FAILED");
	}
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
	//D3DXMATRIX rx, ry;
	//D3DXMatrixRotationX(&rx, 3.14f / 4.0f);

	//static float y = 0.0f;
	//D3DXMatrixRotationY(&ry, y);
	//y += 0.001f;
	//if (y >= 6.28f)
	//	y = 0.0f;

	//D3DXMATRIX p = rx * ry;
	//theDevice->SetTransform(D3DTS_WORLD, &p);

	D3DXHANDLE hTech = m_effect->GetTechniqueByName("Teapot");
	m_effect->SetTechnique(hTech);
	UINT numPasses = 0;
	m_effect->Begin(&numPasses, 0);

	for (auto i = 0u; i < numPasses; i++)
	{
		m_effect->BeginPass(i);
		m_mesh->DrawSubset(0);
		m_effect->EndPass();
	}
	m_effect->End();
	
}