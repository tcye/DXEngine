#pragma once

class Scene;

class Director : public Singleton<Director>
{
public:
	bool Init();
	void Cleanup();

	void Update();
	void Render();

	void PushScene(Ptr<Scene>);
	void PopScene();
	void ReplaceScene(Ptr<Scene>);
	void RunWithScene(Ptr<Scene>);

	Ptr<Scene> GetRunningScene();

	void Pause();
	void Resume();

private:
	bool m_run;
	std::vector<Ptr<Scene>> m_scenes;
};