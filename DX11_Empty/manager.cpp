#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"

CScene* Manager:: m_scene;


void Manager::Init()
{
	Renderer::Init();
	
	m_scene = new CScene();
	m_scene->Init();
}


void Manager::Uninit()
{
	m_scene->Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	m_scene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	m_scene->Draw();
	
	Renderer::End();

}
