#include "Stdafx.h"
#include "Core.h"
#include "Game.h"
#include "Camera.h"
#include "Director.h"
#include "Scene.h"
#include "XFileObject.h"

XFileObject::XFileObject(const std::string& xfile)
{
	LoadResources(xfile);
	m_position = { 0.f, 0.f, 0.f };
	m_rotation = { 0.f, 0.f, 0.f };
	m_scaling = { 1.f, 1.f, 1.f };
}

XFileObject::~XFileObject()
{
	SAFE_RELEASE(m_mesh);
	for (auto& tex : m_textures)
		SAFE_RELEASE(tex);
}

void XFileObject::LoadResources(const std::string& xfile)
{
	ID3DXBuffer* adjBuffer = nullptr;
	ID3DXBuffer* mtrlBuffer = nullptr;
	DWORD numMtrls = 0;
	HRESULT hr = D3DXLoadMeshFromX(xfile.c_str(), D3DXMESH_MANAGED, theDevice,
		&adjBuffer,	&mtrlBuffer, 0,	&numMtrls, &m_mesh);
	if (FAILED(hr))
		Error("X File Load Error");

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();
		for (size_t i = 0; i < numMtrls; i++)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
			m_mtrls.push_back(mtrls[i].MatD3D);

			if (mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(theDevice, mtrls[i].pTextureFilename,	&tex);
				m_textures.push_back(tex);
			}
			else
				m_textures.push_back(0);
		}
	}
	SAFE_RELEASE(mtrlBuffer);
}

void XFileObject::Update()
{

}

void XFileObject::Render()
{
	theLight->SetLightRenderState();

	theDevice->SetTransform(D3DTS_WORLD, &GetTransformMatrix());
	theDevice->SetTransform(D3DTS_VIEW, &(theCamera->GetViewMatrix()));
	theDevice->SetTransform(D3DTS_PROJECTION, &(theCamera->GetProjMatrix()));
	for (size_t i = 0; i < m_mtrls.size(); i++)
	{
		theDevice->SetMaterial(&m_mtrls[i]);
		theDevice->SetTexture(0, m_textures[i]);
		m_mesh->DrawSubset(i);
	}

}

const D3DXVECTOR3& XFileObject::GetPosition()
{
	return m_position;
}

void XFileObject::SetPosition(const D3DXVECTOR3& pos)
{
	m_position = pos;
}

const D3DXVECTOR3& XFileObject::GetRotation()
{
	return m_rotation;
}

void XFileObject::SetRotation(const D3DXVECTOR3& rotation)
{
	m_rotation = rotation;
}

const D3DXVECTOR3& XFileObject::GetScaling()
{
	return m_scaling;
}

void XFileObject::SetScaling(const D3DXVECTOR3& scaling)
{
	m_scaling = scaling;
}

const D3DXMATRIX XFileObject::GetTransformMatrix()
{
	D3DXMATRIX move, rotx, roty, rotz, scale;
	D3DXMatrixTranslation(&move, m_position.x, m_position.y, m_position.z);
	D3DXMatrixRotationX(&rotx, D3DXToRadian(m_rotation.x));
	D3DXMatrixRotationY(&roty, D3DXToRadian(m_rotation.y));
	D3DXMatrixRotationZ(&rotz, D3DXToRadian(m_rotation.z));
	D3DXMatrixScaling(&scale, m_scaling.x, m_scaling.y, m_scaling.z);

	return rotx * roty *rotz * scale * move;
}
