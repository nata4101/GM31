#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "Field.h"
#include "Camera.h"
#include "model.h"
#include "Player.h"
#include <list>

std::list<CGameObject*> g_GameObject;

void Manager::Init()
{
	Renderer::Init();

	CCamera* camera = new CCamera();
	camera->Init();
	g_GameObject.push_back(camera);

	CField* field = new CField();
	field->Init();
	g_GameObject.push_back(field);
	
	CPlayer* player = new CPlayer();
	player->Init();
	g_GameObject.push_back(player);

	CPolygon2D* polygon2d = new CPolygon2D();
	polygon2d->Init();
	g_GameObject.push_back(polygon2d);
}


void Manager::Uninit()
{
	for (CGameObject* object : g_GameObject) {
		object->Uninit();
		delete object;
	}
	g_GameObject.clear();
	Renderer::Uninit();
}

void Manager::Update()
{
	for (CGameObject* object : g_GameObject) {
		object->Update();

	}
}

void Manager::Draw()
{
	Renderer::Begin();

	for (CGameObject* object : g_GameObject) {
		object->Draw();

	}

	Renderer::End();

}
