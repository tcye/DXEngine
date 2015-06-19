#pragma once

class SkyBox : public GameObject
{
public:
	SkyBox();
	~SkyBox();

	void Update();
	void Render();

private:
	ID3DXMesh* m_mesh;
	ID3DXEffect* m_effect;
	D3DXHANDLE m_hViewInv;
	D3DXHANDLE m_hProj;
	D3DXHANDLE m_hTex;
};