#pragma once
#include "Core.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Update();
	void Render();

	void AddGameObject(Ptr<GameObject>);

private:
	std::vector<Ptr<GameObject>> m_objs;
};
