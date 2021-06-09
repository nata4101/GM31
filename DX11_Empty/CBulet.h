#pragma once
#include "GameObject.h"
#include <string>

class CBullet : public CGameObject
{
public:
	CBullet(){}
	virtual ~CBullet(){}

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

protected:
	D3DXVECTOR3 dir;
	float speed;
	std::string m_model_name = "bullet_model";
};

