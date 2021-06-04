#pragma once
#include "GameObject.h"

class CPolygon2D :public CGameObject
{
public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;


};

