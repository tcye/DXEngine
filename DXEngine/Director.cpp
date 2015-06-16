#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Director.h"
#include "Scene.h"

bool Director::Init()
{
	m_run = false;
	return true;
}

void Director::Cleanup()
{
	m_scenes.clear();
	m_run = false;
}

void Director::Update()
{
	if (m_run && !m_scenes.empty())
		m_scenes.back()->Update();
}

void Director::Render()
{
	theDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		0xffffffff, 1.0f, 0);
	theDevice->BeginScene();

	if (!m_scenes.empty())
		m_scenes.back()->Render();

	theDevice->EndScene();
	theDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void Director::PushScene(Ptr<Scene> s)
{
	m_scenes.push_back(s);
}

void Director::PopScene()
{
	if (!m_scenes.empty())
	{
		m_scenes.pop_back();
	}
}

void Director::ReplaceScene(Ptr<Scene> s)
{
	PopScene();
	PushScene(s);
}

void Director::RunWithScene(Ptr<Scene> s)
{
	PushScene(s);
	m_run = true;
}

void Director::Pause()
{
	m_run = false;
}

void Director::Resume()
{
	m_run = true;
}
