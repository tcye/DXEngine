#pragma once

#include <memory>

#define Ptr std::shared_ptr
#define Create std::make_shared

template <class T>
class Singleton
{
public:
	static Ptr<T> GetInstance()
	{
		static Ptr<T> instance = nullptr;
		if (instance == nullptr)
			instance = Create<T>();
		return instance;
	}
};

#define Warn(msg) MessageBox(NULL, (msg), "Warn!", MB_OK)
#define Error(msg) MessageBox(NULL, (msg), "Error!", MB_OK)

#define theGame (Game::GetInstance())
#define theDevice (Game::GetInstance()->GetDeviceHandle())
#define theWindow (Game::GetInstance()->GetWindowHandle())
#define theDirector (Director::GetInstance())
#define theInput (Input::GetInstance())
#define theTime (Time::GetInstance())
#define theCamera (Director::GetInstance()->GetRunningScene()->GetCamera())

#define SAFE_RELEASE(p) if (p) { p->Release(); p = nullptr; }

class GameObject
{
public:
	virtual ~GameObject() { }
	virtual void Update() = 0;
	virtual void Render() = 0;
};

void RenderWithEffect(ID3DXEffect* effect, const char* tech, std::function<void()> func);