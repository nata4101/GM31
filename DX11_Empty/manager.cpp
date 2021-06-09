#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"
#include "ModelManager.h"
#include "input.h"

CScene* Manager:: m_scene;

CModelManager g_model_manager;

void Manager::Init()
{
	Input::Init();
	Renderer::Init();

	g_model_manager.Init();
	
	m_scene = new CScene();
	m_scene->Init();
}


void Manager::Uninit()
{

	m_scene->Uninit();
	Renderer::Uninit();
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
	Renderer::Begin();

	m_scene->Draw();
	
	Renderer::End();

}
