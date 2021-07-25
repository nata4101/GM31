#pragma once



class CSprite : public CGameObject
{
public:
	CSprite(){}
	~CSprite(){}

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetResource(const char* file_name);

private:
	UINT texture_index = 0;
	ID3D11Buffer*	m_VertexBuffer = nullptr;
};

