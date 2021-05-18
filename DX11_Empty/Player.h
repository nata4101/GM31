#pragma once


class CPlayer
{
private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_scale;

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