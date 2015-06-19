#pragma once

class Camera : public GameObject
{
public:
	Camera();
	~Camera();

	void Update();
	void Render();

	const D3DXMATRIX& GetViewMatrix()
	{
		return m_matView;
	}

	const D3DXMATRIX& GetProjMatrix()
	{
		return m_matProj;
	}

	const D3DXMATRIX& GetViewProjMatrix()
	{
		return m_matViewProj;
	}

	const D3DXMATRIX& GetViewInvMatrix()
	{
		return m_matViewInv;
	}

	void SetMoveSpeed(float speed)
	{
		m_moveSpeed = speed;
	}

private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_target;
	D3DXVECTOR3 m_up;

	D3DXMATRIX m_matView;
	D3DXMATRIX m_matViewInv;
	D3DXMATRIX m_matProj;
	D3DXMATRIX m_matViewProj;

	float m_moveSpeed;
};