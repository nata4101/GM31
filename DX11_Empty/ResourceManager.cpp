#include "main.h"
#include "renderer.h"
#include "ResourceManager.h"


void CResourceManager::Init(void)
{
	resource_count = 0;

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

UINT CResourceManager::LoadModelPac(const char * file_name)
{
	for (ModelPac* pac : model_list) {
		if (pac->file_name == file_name) return pac->model_index;
	}

	resource_count++;

	ModelPac* buff = new ModelPac();

	buff->model = new Model();

	buff->model->Load(file_name);
	buff->file_name = file_name;
	buff->model_index = resource_count;

	model_list.push_back(buff);

	return resource_count;
}

UINT CResourceManager::LoadTexturePac(const char * file_name)
{
	Renderer* renderer = Renderer::GetInstance();

	for (TexturePac* pac : texture_list) {
		if (pac->file_name == file_name) return pac->texture_index;
	}

	resource_count++;

	TexturePac* buff = new TexturePac();

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		renderer->GetDevice(),
		file_name,
		NULL,
		NULL,
		&buff->texture,
		NULL);

	assert(buff->texture);

	buff->file_name = file_name;
	buff->texture_index = resource_count;

	texture_list.push_back(buff);

	return resource_count;
}

Model * CResourceManager::GetModel(UINT index)
{
	for (ModelPac* pac : model_list) {
		if (pac->model_index == index) return pac->model;
	}

	return NULL;
}

ID3D11ShaderResourceView * CResourceManager::GetTexture(UINT index)
{
	for (TexturePac* pac : texture_list) {
		if (pac->texture_index == index) return pac->texture;
	}

	return NULL;
}

void CResourceManager::UnloadModelPac(UINT index)
{
	auto itr = model_list.begin();

	for (ModelPac* pac : model_list) {
		if (pac->model_index == index) {
			pac->model->Unload();
			delete pac->model;
			model_list.erase(itr);
			break;
		}
		itr++;
	}
	return;
}

void CResourceManager::UnloadModelPacAll(void)
{
	for (ModelPac* pac : model_list) {

		pac->model->Unload();
		delete pac->model;
	}
	model_list.clear();
	return;
}

void CResourceManager::UnloadTexturePac(UINT index)
{
}

void CResourceManager::UnloadTexturePacAll(void)
{
}
