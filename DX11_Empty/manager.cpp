#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"
#include "ModelManager.h"
#include "input.h"


CModelManager g_model_manager;

Renderer* renderer;

void Manager::Init()
{
	renderer = Renderer::GetInstance();
	Input::Init();
	renderer->Renderer::Init();

	g_model_manager.Init();
	
	m_scene = new CScene();
	m_scene->Init();
}


void Manager::Uninit()
{

	m_scene->Uninit();
	renderer->Uninit();
	CModelManager::UnloadModelPacAll();
	Input::Uninit();
}

void Manager::Update()
{
	Input::Update();
	m_scene->Update();
}

void Manager::Draw()
{
	renderer->Begin();

	m_scene->Draw();
	
	renderer->End();

}
