#pragma once
#include "main.h"

class CGameObject
{
public:
	CGameObject(){}
	virtual ~CGameObject(){}
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetPosition(D3DXVECTOR3 pos) { m_position = pos; }

	void SetRotation(D3DXVECTOR3 rad) { m_rotation = rad; }

	void SetScale(D3DXVECTOR3 size) { m_scale = size; }

	D3DXVECTOR3 GetPosition() { return m_position; }

	D3DXVECTOR3 GetRotation() { return m_rotation; }

	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_rotation.y, m_rotation.x,m_rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetUp() 
	{
		D3DXVECTOR3 up;

		D3DXVec3Cross(&up, &GetForward(), &GetRight());

		return up;

	}

	D3DXVECTOR3 GetRight()
	{
		D3DXMATRIX rot, buff;
		D3DXMatrixRotationYawPitchRoll(&rot, m_rotation.y, m_rotation.x, m_rotation.z);
		rot = *D3DXMatrixRotationY(&buff, (3.14f / 2.f)) * rot;

		D3DXVECTOR3 right;
		right.x = rot._31;
		right.y = rot._32;
		right.z = rot._33;

		return right;

	}

	D3DXVECTOR3 GetScale() { return m_scale; }

	void SetDestroy() { m_destroy = true; }

	bool Destroy()
	{
		if (m_destroy) {
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
private:
protected:
	bool m_destroy = false;

	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_scale;

};

