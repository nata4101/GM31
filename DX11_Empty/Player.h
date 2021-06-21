#pragma once
#include "GameObject.h"
#include <string>

class CPlayer : public CGameObject
{
private:

	static UINT model_index;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};