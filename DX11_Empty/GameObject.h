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

	void SetPosition(XMFLOAT3 pos) { m_position = pos; }

	void SetRotation(XMFLOAT3 rad) { m_rotation = rad; }

	void SetScale(XMFLOAT3 size) { m_scale = size; }

	XMFLOAT3 GetPosition() { return m_position; }

	XMFLOAT3 GetRotation() { return m_rotation; }

	XMFLOAT3 GetScale() { return m_scale; }

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

	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMFLOAT3 m_scale;

};

