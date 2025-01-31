#pragma once

#include <list>
#include <typeinfo>
#include <vector>
#include "GameObject.h"



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

	virtual void Init() = 0;
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
			//�����_��
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
		T* obj;
		for (int i = 0; i < MAX_LAYER; i++) {
			for (CGameObject* object : m_gameobject[i])
				if (typeid(*object) == typeid(T))
				{
					obj = (T*)object;
					return  obj;
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

