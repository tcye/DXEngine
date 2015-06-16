#pragma once
#include "Core.h"
#include <vector>
class GameObject;

struct Vertex
{
	Vertex(){}

	Vertex(float x, float y, float z, float nx, float ny, float nz)
	{
		_x = x;  _y = y;	_z = z;
		_nx = nx; _ny = ny; _nz = nz;
	}
	float _x, _y, _z;
	float _nx, _ny, _nz;
	static const DWORD FVF;
};

class Scene
{
public:
	Scene();
	~Scene();

	void Update();
	void Render();

private:
	IDirect3DVertexBuffer9* m_vb;
};