#pragma once
#include "GameObject.h"

using namespace DirectX;

class CCamera : public CGameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	DXMatrix GetViewMatrix() { return m_viewMatrix; }
private:
	DXVector3 m_target;
	DXMatrix m_viewMatrix;
};
