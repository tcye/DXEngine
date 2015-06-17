#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Camera.h"

Camera::Camera()
{
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, -3.0f);
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{

}

void Camera::Update()
{

}

void Camera::Render()
{
	D3DXMATRIX v;
	D3DXMatrixLookAtLH(&v, &m_position, &m_target, &m_up);
	theDevice->SetTransform(D3DTS_VIEW, &v);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f,
		(float)theGame->GetWidth() / (float)theGame->GetHeight(),
		1.0f, 1000.0f);
	theDevice->SetTransform(D3DTS_PROJECTION, &proj);
}
