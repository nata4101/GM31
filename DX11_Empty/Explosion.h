#pragma once

#include "GameObject.h"

class CExplosion : public CGameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	
private:
	static UINT texture_index;
	ID3D11Buffer* m_VertexBuffer = NULL;
	float m_count;
};

