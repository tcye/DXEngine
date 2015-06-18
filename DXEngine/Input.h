#pragma once
#include "Core.h"

class Input : public Singleton<Input>
{
public:
	bool Init();
	void Cleanup();

	D3DXVECTOR2 GetMousePosition();
	bool GetKey(unsigned int);

private:
	friend class Game;
	void RefreshInputState();

private:
	unsigned char m_keys[256];
	D3DXVECTOR2 m_mousePosition;

};