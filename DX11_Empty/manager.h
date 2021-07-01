#pragma once
#include "Singleton.h"

class Manager : public Singleton<Manager>
{
private:
	 class CScene* m_scene = nullptr;
public:
	 void Init();
	 void Uninit();
	 void Update();
	 void Draw();

	 template <typename T>
	 void SetScene()
	 {
		 if (m_scene) {
			 m_scene->Uninit();
			 delete m_scene;
		 }

		 T* scene = new T();
		 m_scene = scene;
		 scene->Init();
	 }

	 class CScene* GetScene(void) { return m_scene; }
};