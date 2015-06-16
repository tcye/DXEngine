#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Scene.h"

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;

const D3DXCOLOR      WHITE(D3DCOLOR_XRGB(255, 255, 255));
const D3DXCOLOR      BLACK(D3DCOLOR_XRGB(0, 0, 0));
const D3DXCOLOR        RED(D3DCOLOR_XRGB(255, 0, 0));
const D3DXCOLOR      GREEN(D3DCOLOR_XRGB(0, 255, 0));
const D3DXCOLOR       BLUE(D3DCOLOR_XRGB(0, 0, 255));
const D3DXCOLOR     YELLOW(D3DCOLOR_XRGB(255, 255, 0));
const D3DXCOLOR       CYAN(D3DCOLOR_XRGB(0, 255, 255));
const D3DXCOLOR    MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

Scene::Scene()
{
	theDevice->CreateVertexBuffer(
		12 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&m_vb, 0);
	Vertex* v;
	m_vb->Lock(0, 0, (void**)&v, 0);

	// front face
	v[0] = Vertex(-1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);
	v[1] = Vertex(0.0f, 1.0f, 0.0f, 0.0f, 0.707f, -0.707f);
	v[2] = Vertex(1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);

	// left face
	v[3] = Vertex(-1.0f, 0.0f, 1.0f, -0.707f, 0.707f, 0.0f);
	v[4] = Vertex(0.0f, 1.0f, 0.0f, -0.707f, 0.707f, 0.0f);
	v[5] = Vertex(-1.0f, 0.0f, -1.0f, -0.707f, 0.707f, 0.0f);

	// right face
	v[6] = Vertex(1.0f, 0.0f, -1.0f, 0.707f, 0.707f, 0.0f);
	v[7] = Vertex(0.0f, 1.0f, 0.0f, 0.707f, 0.707f, 0.0f);
	v[8] = Vertex(1.0f, 0.0f, 1.0f, 0.707f, 0.707f, 0.0f);

	// back face
	v[9] = Vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.707f, 0.707f);
	v[10] = Vertex(0.0f, 1.0f, 0.0f, 0.0f, 0.707f, 0.707f);
	v[11] = Vertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.707f, 0.707f);
	m_vb->Unlock();

	D3DMATERIAL9 mtrl;
	mtrl.Ambient = WHITE;
	mtrl.Diffuse = WHITE;
	mtrl.Specular = WHITE;
	mtrl.Emissive = BLACK;
	mtrl.Power = 5.0f;

	
	theDevice->SetMaterial(&mtrl);

	D3DLIGHT9 dir;
	::ZeroMemory(&dir, sizeof(dir));
	dir.Type = D3DLIGHT_DIRECTIONAL;
	dir.Diffuse = WHITE;
	dir.Specular = WHITE * 0.3f;
	dir.Ambient = WHITE * 0.6f;
	dir.Direction = D3DXVECTOR3(1.0F, 0.0F, 0.0F);
	theDevice->SetLight(0, &dir);
	theDevice->LightEnable(0, true);
	theDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	theDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	
	theDevice->SetStreamSource(0, m_vb, 0, sizeof(Vertex));
	theDevice->SetFVF(Vertex::FVF);

	D3DXVECTOR3 position(0, 0, -5.0f);
	D3DXVECTOR3 target(0, 0, 0);
	D3DXVECTOR3 up(0, 1.0, 0);

	D3DXMATRIX mv;
	D3DXMatrixLookAtLH(&mv, &position, &target, &up);
	theDevice->SetTransform(D3DTS_VIEW, &mv);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, 800.0f / 600, 1.0f, 1000.0f);
	theDevice->SetTransform(D3DTS_PROJECTION, &proj);

	//TheDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

}

Scene::~Scene()
{

}

void Scene::Update()
{

}

void Scene::Render()
{
	theDevice->DrawPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		4);
}
