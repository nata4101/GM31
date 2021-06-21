#pragma once
#include "Singleton.h"

class Manager : public Singleton<Manager>
{

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	class CScene* GetScene(void) { return m_scene; }
private :
	class CScene* m_scene;
};