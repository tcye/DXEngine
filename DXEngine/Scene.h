#pragma once
#include "Core.h"
#include "Camera.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Update();
	void Render();

	void AddGameObject(Ptr<GameObject>);
	void AddGameObject(Ptr<Camera>);

	Ptr<Camera> GetCamera()
	{
		return m_camera;
	}

private:
	std::vector<Ptr<GameObject>> m_objs;
	Ptr<Camera> m_camera;
};
