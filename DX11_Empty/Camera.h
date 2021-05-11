#pragma once

using namespace DirectX;

class CCamera
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	XMVECTOR m_position;
	XMVECTOR m_target;
};
