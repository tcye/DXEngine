#pragma once

class DirectionalLight : public GameObject
{
public:
	DirectionalLight(const D3DXCOLOR& color, const D3DXVECTOR3& dir);
	~DirectionalLight();

	D3DXVECTOR3 GetLightDirection()
	{
		return m_d3dlight.Direction;
	}

	D3DXCOLOR GetLightColor()
	{
		return m_d3dlight.Diffuse;
	}

	void SetLightRenderState();

	void Update() { }
	void Render() { }

private:
	D3DLIGHT9 m_d3dlight;
};