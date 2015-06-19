#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Camera.h"
#include "Director.h"
#include "Scene.h"
#include "SkyBox.h"

struct Vertex
{
	float x, y, z;
};

const int rect_x = 50;
const int rect_y = 50;
const int rect_z = 3;

SkyBox::SkyBox()
{
	// Create a rect before the camera to render the sky
	D3DXCreateMeshFVF(2, 4,	0, D3DFVF_XYZ, theDevice, &m_mesh);
	Vertex* v;
	m_mesh->LockVertexBuffer(0, (void**)&v);
	v[0] = { -rect_x, rect_y, rect_z };
	v[1] = { rect_x, rect_y, rect_z };
	v[2] = { -rect_x, -rect_y, rect_z };
	v[3] = { rect_x, -rect_y, rect_z };
	m_mesh->UnlockVertexBuffer();
	WORD* i;
	m_mesh->LockIndexBuffer(0, (void**)&i);
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 1; i[4] = 3; i[5] = 2;
	m_mesh->UnlockIndexBuffer();

	// Create effect
	ID3DXBuffer* errorBuffer;
	D3DXCreateEffectFromFile(theDevice, "SkyBox.fx", 0, 0,
		D3DXSHADER_DEBUG, 0, &m_effect, &errorBuffer);

	if (errorBuffer)
	{
		Error((char*)errorBuffer->GetBufferPointer());
		errorBuffer->Release();
	}

	// Set effect params
	m_hViewInv = m_effect->GetParameterByName(0, "matViewInv");
	m_hProj = m_effect->GetParameterByName(0, "matProj");
	m_hTex = m_effect->GetParameterByName(0, "texSky");

	// Load and set cube texture
	IDirect3DCubeTexture9* texSky;
	D3DXCreateCubeTextureFromFile(theDevice, "SkyBox.dds", &texSky);
	m_effect->SetTexture(m_hTex, texSky);
	texSky->Release();
}

SkyBox::~SkyBox()
{
	SAFE_RELEASE(m_mesh);
	SAFE_RELEASE(m_effect);
}

void SkyBox::Update()
{

}

void SkyBox::Render()
{
	m_effect->SetMatrix(m_hProj, &(theCamera->GetProjMatrix()));
	m_effect->SetMatrix(m_hViewInv, &(theCamera->GetViewInvMatrix()));

	RenderWithEffect(m_effect, "SkyBox", [&](){	
		m_mesh->DrawSubset(0);
	});
}