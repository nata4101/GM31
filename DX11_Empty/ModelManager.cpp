#include "main.h"
#include "renderer.h"
#include "ModelManager.h"

list<CModelManager::ModelPac*> CModelManager:: model_list;

CModelManager:: ShaderPac CModelManager:: shader_pac[SHADERMAX];

void CModelManager::Init(void)
{
	Renderer* renderer = Renderer::GetInstance();
	renderer->CreateVertexShader(
		&shader_pac[TWODSHADER].m_vertexshader,
		&shader_pac[TWODSHADER].m_vertexlayout,
		"unlitTextureVS.cso");

	renderer->CreatePixelShader(&shader_pac[TWODSHADER].m_pixelshader, "unlitTexturePS.cso");

	renderer->CreateVertexShader(
		&shader_pac[THREEDSHADER].m_vertexshader,
		&shader_pac[THREEDSHADER].m_vertexlayout,
		"vertexLightingVS.cso");

	renderer->CreatePixelShader(&shader_pac[THREEDSHADER].m_pixelshader, "vertexLightingPS.cso");
}

void CModelManager::LoadModelPac(string * model_name, const char * file_name)
{
	for (ModelPac* pac : model_list) {
		if (pac->model_name == *model_name) return;
	}

	ModelPac* buff = new ModelPac();

	buff->model = new Model();

	buff->model->Load(file_name);
	buff->model_name = *model_name;

	model_list.push_back(buff);

	return;
}

Model * CModelManager::GetModel(string * name)
{
	for (ModelPac* pac : model_list) {
		if (pac->model_name == *name) return pac->model;
	}

	return NULL;
}

void CModelManager::UnloadModelPac(string * name)
{
	auto itr = model_list.begin();

	for (ModelPac* pac : model_list) {
		if (pac->model_name == *name) {
			pac->model->Unload();
			delete pac->model;
			model_list.erase(itr);
			break;
		}
		itr++;
	}
	return;
}

void CModelManager::UnloadModelPacAll(void)
{
	for (ModelPac* pac : model_list) {

		pac->model->Unload();
		delete pac->model;
	}
	model_list.clear();
	return;
}
