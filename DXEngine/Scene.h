#pragma once
#include "Core.h"
#include "Camera.h"
#include "DirectionalLight.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Update();
	void Render();

	void AddGameObject(Ptr<GameObject>);
	void AddGameObject(Ptr<Camera>);
	void AddGameObject(Ptr<DirectionalLight>);

	Ptr<Camera> GetCamera()
	{
		return m_camera;
	}

	Ptr<DirectionalLight> GetLight()
	{
		return m_light;
	}

private:
	std::vector<Ptr<GameObject>> m_objs;
	Ptr<Camera> m_camera;
	Ptr<DirectionalLight> m_light;
};
