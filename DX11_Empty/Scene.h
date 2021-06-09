#pragma once
#include "polygon2D.h"
#include "Field.h"
#include "Camera.h"
#include "Enemy.h"
#include "model.h"
#include "Player.h"
#include "CBulet.h"
#include <list>
#include <typeinfo>
#include <vector>
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

		AddGameObject<CEnemy>()->SetPosition(D3DXVECTOR3(-3, 1, 5));

		AddGameObject<CEnemy>()->SetPosition(D3DXVECTOR3(0, 1, 5));

		AddGameObject<CEnemy>()->SetPosition(D3DXVECTOR3(3, 1, 5));

		//AddGameObject<CBullet>();

		//AddGameObject<CPolygon2D>();

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
		//ƒ‰ƒ€ƒ_Ž®
		m_gameobject.remove_if([](CGameObject* object) {return object->Destroy(); });
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

	template <typename T>
	T* GetGameObject()
	{
		for(CGameObject* object : m_gameobject)
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		return NULL;
	}

	template <typename T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objects;
		for (CGameObject* object : m_gameobject)
		{
			if (typeid(*object) == typeid(T)) {
				objects.push_back((T*)object);
			}
		}
		return objects;
	}


protected:
	std::list<CGameObject*> m_gameobject;
 };

