#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Input.h"

bool Input::Init()
{
	return true;
}

void Input::Cleanup()
{

}

void Input::RefreshInputState()
{
	POINT mousePosit;
	GetCursorPos(&mousePosit);
	ScreenToClient(theWindow, &mousePosit);
	m_mousePosition.x = (float)mousePosit.x;
	m_mousePosition.y = (float)mousePosit.y;

	GetKeyboardState(m_keys);
}

bool Input::GetKey(unsigned int vk)
{
	return (m_keys[vk] & 0x80) != 0;
}

D3DXVECTOR2 Input::GetMousePosition()
{
	return m_mousePosition;
}
