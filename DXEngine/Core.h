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
#define theDirector (Director::GetInstance())
#define theInput (Input::GetInstance())

