#pragma once

class XFileObject : public GameObject
{
public:
	XFileObject(const std::string& xfile);
	~XFileObject();

	void Update();
	void Render();

	const D3DXVECTOR3& GetPosition();
	void SetPosition(const D3DXVECTOR3&);

	const D3DXVECTOR3& GetRotation();
	void SetRotation(const D3DXVECTOR3&);

	const D3DXVECTOR3& GetScaling();
	void SetScaling(const D3DXVECTOR3&);

	const D3DXMATRIX GetTransformMatrix();

private:
	void LoadResources(const std::string& xfile);

private:
	ID3DXMesh* m_mesh;
	std::vector<D3DMATERIAL9> m_mtrls;
	std::vector<IDirect3DTexture9*> m_textures;

	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_scaling;
};