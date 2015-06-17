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

};