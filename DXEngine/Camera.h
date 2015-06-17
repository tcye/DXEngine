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
};