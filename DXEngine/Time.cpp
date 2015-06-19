#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Time.h"

bool Time::Init()
{
	float t = 0.001f * (float)timeGetTime();
	m_curTime = t;
	m_lastTime = t;
	m_deltaTime = 0.0f;
	return true;
}

void Time::Cleanup()
{

}

void Time::RefreshTimeState()
{
	m_curTime = 0.001f * (float)timeGetTime();
	m_deltaTime = m_curTime - m_lastTime;
	m_lastTime = m_curTime;
}

float Time::GetDeltaTime()
{
	return m_deltaTime;
}

float Time::GetFrameStartTime()
{
	return m_curTime;
}
