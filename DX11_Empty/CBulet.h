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

	void SetDirection(D3DXVECTOR3 forward) { dir = forward; }

protected:
	D3DXVECTOR3 dir;
	float speed;
	static UINT model_index;
};

