#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Scene.h"
#include "Camera.h"
#include "Teapot.h"
#include "SkyBox.h"
#include "XFileObject.h"

Scene::Scene()
{
	SetCurrentDirectory("Media");
	AddGameObject(Create<DirectionalLight>(D3DXCOLOR(1.f, 1.f, 1.f, 1.f), D3DXVECTOR3(1.f, -1.f, 1.f)));
	AddGameObject(Create<Camera>());
	AddGameObject(Create<SkyBox>("SkyBox.dds"));

	auto man = Create<XFileObject>("tiny.x");
	auto terrain = Create<XFileObject>("Terrain.x");
	auto house = Create<XFileObject>("House.x");
	auto rock0 = Create<XFileObject>("rock.x");
	auto rock1 = Create<XFileObject>("rock.x");
	auto rock2 = Create<XFileObject>("rock.x");

	man->SetPosition({ 0.0f, 5.0f, -20.0f });
	man->SetRotation({ -90.f, 215.0f, 0.f});
	man->SetScaling({ 0.02f, 0.02f, 0.02f });
	house->SetRotation({ 0.0f, 35.0f, 0.0f });

	rock0->SetPosition({ 3.0f, 0.0f, -25.0f });
	rock1->SetPosition({ -0.0f, 0.0f, -25.0f });
	rock2->SetPosition({ -3.0f, 0.0f, -25.0f });

	AddGameObject(terrain);
	AddGameObject(man);
	AddGameObject(house);
	AddGameObject(rock0);
	AddGameObject(rock1);
	AddGameObject(rock2);
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

void Scene::AddGameObject(Ptr<DirectionalLight> obj)
{
	m_light = obj;
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
