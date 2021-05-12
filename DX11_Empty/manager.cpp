#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "Camera.h"
#include "Field.h"

CPolygon2D* g_polygon2d = NULL;
CField *	g_field = NULL;
CCamera*	g_camera = NULL;

void Manager::Init()
{
	Renderer::Init();

	g_polygon2d = new CPolygon2D();
	g_polygon2d->Init();

	g_field = new CField();
	g_field->Init();

	g_camera = new CCamera();
	g_camera->Init();

}


void Manager::Uninit()
{
	g_polygon2d->Uninit();
	delete g_polygon2d;

	g_field->Uninit();
	delete g_field;

	g_camera->Uninit();
	delete g_camera;

	Renderer::Uninit();
}

void Manager::Update()
{
	g_camera->Update();
	g_field->Update();
	g_polygon2d->Update();
}

void Manager::Draw()
{
	Renderer::Begin();
	g_camera->Draw();

	g_field->Draw();

	g_polygon2d->Draw();

	Renderer::End();
}
