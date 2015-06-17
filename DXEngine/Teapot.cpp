#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Teapot.h"

Teapot::Teapot()
{
	D3DXCreateTeapot(theDevice, &m_mesh, nullptr);
	DWORD fvf = m_mesh->GetFVF();
	Warn(std::to_string(fvf).c_str());

	
}

Teapot::~Teapot()
{
	m_mesh->Release();
	m_mesh = nullptr;
}

void Teapot::Update()
{

}

void Teapot::Render()
{
	theDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	D3DXMATRIX rx, ry;
	D3DXMatrixRotationX(&rx, 3.14f / 4.0f);

	static float y = 0.0f;
	D3DXMatrixRotationY(&ry, y);
	y += 0.005f;
	if (y >= 6.28f)
		y = 0.0f;

	D3DXMATRIX p = rx * ry;
	theDevice->SetTransform(D3DTS_WORLD, &p);

	m_mesh->DrawSubset(0);
}