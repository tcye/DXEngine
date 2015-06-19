#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "Camera.h"

Camera::Camera()
{
	m_up = { 0.0f, 1.0f, 0.0f };
	m_position = { 0.0f, 0.0f, -3.0f };
	m_target = { 0.0f, 0.0f, 0.0f };

	m_moveSpeed = 2.0f;

	D3DXMatrixLookAtLH(&m_matView, &m_position, &m_target, &m_up);
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(45.0f),
		(float)theGame->GetWidth() / (float)theGame->GetHeight(),
		1.0f, 1000.0f);

	m_matViewProj = m_matView * m_matProj;
	D3DXMatrixInverse(&m_matViewInv, nullptr, &m_matView);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	static D3DXVECTOR2 lastMousePosition = theInput->GetMousePosition();
	D3DXMATRIX matViewInv;
	D3DXMatrixInverse(&matViewInv, nullptr, &m_matView);
	
	float moveX = 0.0f, moveY = 0.0f, moveZ = 0.0f;
	if (theInput->GetKey(VK_UP) || theInput->GetKey('W'))
		moveZ += m_moveSpeed * theTime->GetDeltaTime();
	if (theInput->GetKey(VK_DOWN) || theInput->GetKey('S'))
		moveZ -= m_moveSpeed * theTime->GetDeltaTime();
	if (theInput->GetKey(VK_LEFT) || theInput->GetKey('A'))
		moveX -= m_moveSpeed * theTime->GetDeltaTime();
	if (theInput->GetKey(VK_RIGHT) || theInput->GetKey('D'))
		moveX += m_moveSpeed * theTime->GetDeltaTime();
	if (theInput->GetKey(VK_HOME) || theInput->GetKey('Q'))
		moveY += m_moveSpeed * theTime->GetDeltaTime();
	if (theInput->GetKey(VK_END) || theInput->GetKey('E'))
		moveY -= m_moveSpeed * theTime->GetDeltaTime();

	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, moveX, moveY, moveZ);
	matTranslation = m_matView * matTranslation* matViewInv;
	D3DXVec3TransformCoord(&m_position, &m_position, &matTranslation);

	D3DXMATRIX matRotation;
	D3DXMatrixIdentity(&matRotation);
	if (theInput->GetKey(VK_LBUTTON))
	{
		D3DXVECTOR2 curMousePosition = theInput->GetMousePosition();
		float xDiff = curMousePosition.x - lastMousePosition.x;
		float yDiff = curMousePosition.y - lastMousePosition.y;

		D3DXMATRIX matRotationX, matRotationY;
		D3DXMatrixRotationX(&matRotationX, D3DXToRadian(yDiff / 3.0f));
		D3DXMatrixRotationY(&matRotationY, D3DXToRadian(xDiff / 3.0f));
		matRotation = matRotationX * matRotationY;

		lastMousePosition = curMousePosition;
	}
	else
	{
		lastMousePosition = theInput->GetMousePosition();
	}
	matRotation = m_matView * matTranslation * matRotation * matViewInv;
	D3DXVec3TransformCoord(&m_target, &m_target, &matRotation);

	D3DXMatrixLookAtLH(&m_matView, &m_position, &m_target, &m_up);
	m_matViewProj = m_matView * m_matProj;
	D3DXMatrixInverse(&m_matViewInv, nullptr, &m_matView);
}

void Camera::Render()
{

}
