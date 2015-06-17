#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Scene.h"
#include "Camera.h"
#include "Teapot.h"

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
	AddGameObject(Create<Camera>());
	AddGameObject(Create<Teapot>());
}

Scene::~Scene()
{

}

void Scene::AddGameObject(Ptr<GameObject> obj)
{
	m_objs.push_back(obj);
}

void Scene::Update()
{
	for (auto obj : m_objs)
	{
		obj->Update();
	}
}

void Scene::Render()
{
	for (auto obj : m_objs)
	{
		obj->Render();
	}
}
