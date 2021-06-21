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
	XMMATRIX GetViewMatrix() { return m_viewMatrix; }
private:
	XMVECTOR m_target;
	XMMATRIX m_viewMatrix;
};
