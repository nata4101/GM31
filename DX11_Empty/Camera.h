#pragma once
#include "GameObject.h"

class CCamera : public CGameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_target;
};
