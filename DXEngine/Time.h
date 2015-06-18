#pragma once

class Time : public Singleton<Time>
{
public:
	bool Init();
	void Cleanup();

	float GetFrameStartTime();
	float GetLastFrameStartTime();
	float GetDeltaTime();

private:
	friend class Game;
	void RefreshTimeStateBeforeFrame();
	void RefreshTimeStateAfterFrame();

private:
	float m_curTime;
	float m_lastTime;
	float m_deltaTime;
};