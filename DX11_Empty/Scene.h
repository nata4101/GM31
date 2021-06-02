#pragma once
#include "polygon2D.h"
#include "Field.h"
#include "Camera.h"
#include "model.h"
#include "Player.h"
#include <list>
#include "Scene.h"

class CScene
{
public:
	CScene() {}
	virtual ~CScene() {}

	virtual void Init() {
		AddGameObject<CCamera>();

		AddGameObject<CField>();

		AddGameObject<CPlayer>();

		AddGameObject<CPolygon2D>();
	}
	virtual void Uninit() {
		for (CGameObject* object : m_gameobject) {
			object->Uninit();
			delete object;
		}
		m_gameobject.clear();
	}
	virtual void Update() {
		for (CGameObject* object : m_gameobject) {
			object->Update();

		}
	}
	virtual void Draw() {
		for (CGameObject* object : m_gameobject) {
			object->Draw();
		}
	}

	template <typename T>
	T* AddGameObject()
	{
		T* gameObject = new T();
		gameObject->Init();
		m_gameobject.push_back(gameObject);
		return gameObject;
	}

protected:
	std::list<CGameObject*> m_gameobject;
 };

