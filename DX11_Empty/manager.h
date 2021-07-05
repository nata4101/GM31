#pragma once
#include "Singleton.h"

class Manager : public Singleton<Manager>
{

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	class CScene* GetScene(void) { return m_scene; }
private :
	class CScene* m_scene;
};