#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "Field.h"
#include "Camera.h"
#include "model.h"
#include "Player.h"

CCamera* g_camera = NULL;
CPolygon2D* g_polygon2d = NULL;
CField* g_field = NULL;
CPlayer* g_player = NULL;

void Manager::Init()
{
	Renderer::Init();

	g_camera = new CCamera();
	g_camera->Init();

	g_polygon2d = new CPolygon2D();
	g_polygon2d->Init();

	g_field = new CField();
	g_field->Init();

	g_player = new CPlayer();
	g_player->Init();
}


void Manager::Uninit()
{
	g_camera->Uninit();
	delete g_camera;

	g_polygon2d->Uninit();
	delete g_polygon2d;

	g_field->Uninit();
	delete g_field;

	g_player->Uninit();
	delete g_player;

	Renderer::Uninit();
}

void Manager::Update()
{
	g_camera->Update();

	g_polygon2d->Update();

	g_field->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	g_camera->Draw();

	g_field->Draw();

	g_player->Draw();

	g_polygon2d->Draw();

	Renderer::End();

}
