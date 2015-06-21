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
		return m_matView * m_matProj;
	}

	const D3DXMATRIX& GetViewInvMatrix()
	{
		D3DXMatrixInverse(&m_matViewInv, nullptr, &m_matView);
		return m_matViewInv;
	}

	void SetMoveSpeed(float speed)
	{
		m_moveSpeed = speed;
	}

private:
	void UpdateViewMatrix();

private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_look;
	
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matViewInv;
	D3DXMATRIX m_matProj;

	float m_moveSpeed;


};