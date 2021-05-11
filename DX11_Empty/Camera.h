#pragma once

class CCamera
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
