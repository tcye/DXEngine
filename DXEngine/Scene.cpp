#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Scene.h"
#include "Camera.h"
#include "Teapot.h"
#include "SkyBox.h"

Scene::Scene()
{
	AddGameObject(Create<Camera>());
	AddGameObject(Create<SkyBox>());
	AddGameObject(Create<Teapot>());
}

Scene::~Scene()
{

}

void Scene::AddGameObject(Ptr<GameObject> obj)
{
	m_objs.push_back(obj);
}

void Scene::AddGameObject(Ptr<Camera> obj)
{
	m_camera = obj;
}

void Scene::Update()
{
	m_camera->Update();
	for (auto obj : m_objs)
	{
		obj->Update();
	}
}

void Scene::Render()
{
	m_camera->Render();
	for (auto obj : m_objs)
	{
		obj->Render();
	}
}
