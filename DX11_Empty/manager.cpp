#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"

CPolygon2D* g_polygon2d = NULL;

void Manager::Init()
{
	Renderer::Init();

	g_polygon2d = new CPolygon2D();
	g_polygon2d->Init();
}


void Manager::Uninit()
{
	g_polygon2d->Uninit();
	delete g_polygon2d;

	Renderer::Uninit();
}

void Manager::Update()
{
	g_polygon2d->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	g_polygon2d->Draw();

	Renderer::End();
}
