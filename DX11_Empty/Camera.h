#pragma once
#include "GameObject.h"

class CCamera : public CGameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	D3DXMATRIX GetViewMatrix();

private:
	D3DXVECTOR3 m_target;
	D3DXMATRIX m_viewMatirx;
};
