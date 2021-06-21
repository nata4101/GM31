#pragma once

#include "GameObject.h"
#include <string>

class CEnemy : public CGameObject
{
public:
	CEnemy(){}
	virtual ~CEnemy(){}

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();


protected:
	static UINT model_index;
};

