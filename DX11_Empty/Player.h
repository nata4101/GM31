#pragma once
#include "GameObject.h"
#include <string>

class CPlayer : public CGameObject
{
private:

	ID3D11VertexShader* m_vertexshader = NULL;
	ID3D11PixelShader* m_pixelshader = NULL;
	ID3D11InputLayout* m_vertexlayout = NULL;
	static UINT model_index;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};