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
	enum ObjectLayer {
		CAMERA_OBJECT,
		THREED_OBJECT,
		TWOD_OBJECT,
		MAX_LAYER
	};

	CScene() {}
	virtual ~CScene() {}

	virtual void Init() {
		AddGameObject<CCamera>(CAMERA_OBJECT);

		AddGameObject<CField>(THREED_OBJECT);

		AddGameObject<CPlayer>(THREED_OBJECT);

		AddGameObject<CEnemy>(THREED_OBJECT)->SetPosition(D3DXVECTOR3(-3, 1, 5));

		AddGameObject<CEnemy>(THREED_OBJECT)->SetPosition(D3DXVECTOR3(0, 1, 5));

		AddGameObject<CEnemy>(THREED_OBJECT)->SetPosition(D3DXVECTOR3(3, 1, 5));

		//AddGameObject<CBullet>();

		AddGameObject<CPolygon2D>(TWOD_OBJECT);

	}
	virtual void Uninit() {
		for (int i = 0; i < MAX_LAYER; i++) {
			for (CGameObject* object : m_gameobject[i]) {
				object->Uninit();
				delete object;
			}
			m_gameobject[i].clear();
		}
	}
	virtual void Update() {
		for (int i = 0; i < MAX_LAYER; i++) {
			for (CGameObject* object : m_gameobject[i]) {
				object->Update();

			}
			//ƒ‰ƒ€ƒ_Ž®
			m_gameobject[i].remove_if([](CGameObject* object) {return object->Destroy(); });
		}
	}
	virtual void Draw() {
		for (int i = 0; i < MAX_LAYER; i++) {
			for (CGameObject* object : m_gameobject[i]) {
				object->Draw();
			}
		}
	}

	template <typename T>
	T* AddGameObject(ObjectLayer layer)
	{
		T* gameObject = new T();
		m_gameobject[layer].push_back(gameObject);
		gameObject->Init();
		return gameObject;
	}

	template <typename T>
	T* GetGameObject()
	{
		for (int i = 0; i < MAX_LAYER; i++) {
			for (CGameObject* object : m_gameobject)
				if (typeid(*object) == typeid(T))
				{
					return (T*)object;
				}

		}
		return NULL;
		
	}

	template <typename T>
	std::vector<T*> GetGameObjects(ObjectLayer layer)
	{
		std::vector<T*> objects;
		for (CGameObject* object : m_gameobject[layer])
		{
			if (typeid(*object) == typeid(T)) {
				objects.push_back((T*)object);
			}
		}
		return objects;
	}


protected:
	std::list<CGameObject*> m_gameobject[3];
 };

