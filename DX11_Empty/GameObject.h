#pragma once
#include "main.h"

using namespace DirectX;

class CGameObject
{
public:
	CGameObject(){}
	virtual ~CGameObject(){}
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetPosition(DXVector3 pos) { m_position = pos; }

	void SetRotation(DXVector3 rad) { m_rotation = rad; }

	void SetScale(XMFLOAT3 size) { m_scale = size; }

	DXVector3 GetPosition() { return m_position; }

	DXVector3 GetRotation() { return m_rotation; }

	DXVector3 GetScale() { return m_scale; }

	DXVector3 GetForward()
	{
		DXMatrix rot;
		rot = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);

		DXVector3 forward;
		
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	DXVector3 GetRight()
	{
		DXMatrix rot;
		rot = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
		rot = XMMatrixRotationY(3.14f / 2.f) * rot.GetMatrix();

		DXVector3 right;
		right.x = rot._31;
		right.y = rot._32;
		right.z = rot._33;

		return right;

	}

	DXVector3 GetUp()
	{
		DXVector3 up;

		up = XMVector3Cross(GetForward().GetVector(), GetRight().GetVector());

		return up;
	}

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

	DXVector3 m_position;
	DXVector3 m_rotation;
	DXVector3 m_scale;

};

