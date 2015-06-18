#pragma once

class Camera : public GameObject
{
public:
	Camera();
	~Camera();

	void Update();
	void Render();

private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_target;
	D3DXVECTOR3 m_up;

	D3DXMATRIX m_viewMatrix;
	D3DXMATRIX m_projMatrix;

	float m_moveSpeed;
};