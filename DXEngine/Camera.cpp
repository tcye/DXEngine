#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "Camera.h"

Camera::Camera()
{
	m_position = { 0.0f, 10.0f, -50.0f };
	m_right = { 1.0f, 0.0f, 0.0f };
	m_up = { 0.0f, 1.0f, 0.0f };
	m_look = { 0.0f, 0.0f, 1.0f };

	m_moveSpeed = 10.0f;

	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(45.0f),
		(float)theGame->GetWidth() / (float)theGame->GetHeight(),
		1.0f, 1000.0f);

	UpdateViewMatrix();
}

Camera::~Camera()
{

}

void Camera::Update()
{
	static D3DXVECTOR2 lastMousePosition = theInput->GetMousePosition();
	// Rotate the camera
	if (theInput->GetKey(VK_LBUTTON))
	{
		D3DXVECTOR2 curMousePosition = theInput->GetMousePosition();
		float xDiff = curMousePosition.x - lastMousePosition.x;
		float yDiff = curMousePosition.y - lastMousePosition.y;
		lastMousePosition = curMousePosition;

		D3DXMATRIX matRotation;
		if (yDiff != 0)
		{
			D3DXMatrixRotationAxis(&matRotation, &m_right, D3DXToRadian(yDiff / 3.0f));
			D3DXVec3TransformCoord(&m_look, &m_look, &matRotation);
			D3DXVec3TransformCoord(&m_up, &m_up, &matRotation);
		}

		if (xDiff != 0)
		{
			D3DXMatrixRotationAxis(&matRotation, &D3DXVECTOR3(0, 1, 0), D3DXToRadian(xDiff / 3.0f));
			D3DXVec3TransformCoord(&m_look, &m_look, &matRotation);
			D3DXVec3TransformCoord(&m_up, &m_up, &matRotation);
			D3DXVec3TransformCoord(&m_right, &m_right, &matRotation);
		}
	}
	else
	{
		lastMousePosition = theInput->GetMousePosition();
	}
	
	// Move the Camera
	float moveX = 0.0f, moveY = 0.0f, moveZ = 0.0f;
	if (theInput->GetKey(VK_UP) || theInput->GetKey('W'))
		moveZ += 1.0f;
	if (theInput->GetKey(VK_DOWN) || theInput->GetKey('S'))
		moveZ -= 1.0f;
	if (theInput->GetKey(VK_LEFT) || theInput->GetKey('A'))
		moveX -= 1.0f;
	if (theInput->GetKey(VK_RIGHT) || theInput->GetKey('D'))
		moveX += 1.0f;
	if (theInput->GetKey(VK_HOME) || theInput->GetKey('Q'))
		moveY += 1.0f;
	if (theInput->GetKey(VK_END) || theInput->GetKey('E'))
		moveY -= 1.0f;
	D3DXVECTOR3 move = moveX * m_right + moveY * m_up + moveZ * m_look;
	D3DXVec3Normalize(&move, &move);
	m_position += move * m_moveSpeed * theTime->GetDeltaTime();



	UpdateViewMatrix();
}

void Camera::Render()
{

}

void Camera::UpdateViewMatrix()
{
	D3DXVec3Normalize(&m_look, &m_look);
	D3DXVec3Cross(&m_up, &m_look, &m_right);
	D3DXVec3Normalize(&m_up, &m_up);
	D3DXVec3Cross(&m_right, &m_up, &m_look);
	D3DXVec3Normalize(&m_right, &m_right);

	float x = -D3DXVec3Dot(&m_right, &m_position);
	float y = -D3DXVec3Dot(&m_up, &m_position);
	float z = -D3DXVec3Dot(&m_look, &m_position);

	m_matView = D3DXMATRIX(
		m_right.x, m_up.x, m_look.x, 0.0f,
		m_right.y, m_up.y, m_look.y, 0.0f,
		m_right.z, m_up.z, m_look.z, 0.0f,
		x,         y,      z,        1.0f);
}
