#pragma once

class Teapot : public GameObject
{
public:
	Teapot();
	~Teapot();

	void Update();
	void Render();

private:
	ID3DXMesh* m_mesh;
	ID3DXEffect* m_effect;
	D3DXHANDLE m_hWorldViewProj;
};