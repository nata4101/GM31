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

