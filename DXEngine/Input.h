#pragma once
#include "Core.h"

class Input : public Singleton<Input>
{
public:
	bool Init();
	void Cleanup();

	bool IsKeyDown(unsigned int key);

	void KeyDown(unsigned int input);
	void KeyUp(unsigned int input);

private:
	bool m_keys[256];
};