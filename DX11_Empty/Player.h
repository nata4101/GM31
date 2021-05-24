#pragma once
#include "GameObject.h"

class CPlayer : public CGameObject
{
private:

	Model* m_model;

	ID3D11VertexShader* m_vertexshader = NULL;
	ID3D11PixelShader* m_pixelshader = NULL;
	ID3D11InputLayout* m_vertexlayout = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};