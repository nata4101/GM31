#include "Enemy.h"
#include "renderer.h"
#include "ResourceManager.h"

UINT CEnemy::model_index;

void CEnemy::Init()
{
	model_index =  CResourceManager::GetInstance()->LoadModelPac("asset\\model\\torus\\torus.obj");

	m_position = XMFLOAT3(0, 0, 0);
	m_rotation = XMFLOAT3(0, 0, 0);
	m_scale = XMFLOAT3(1, 1, 1);
}

void CEnemy::Uninit()
{
}

void CEnemy::Update()
{
}

void CEnemy::Draw()
{
	Renderer* renderer = Renderer::GetInstance();
	CResourceManager* m_manager = CResourceManager::GetInstance();
	//入力レイアウト設定
	renderer->GetDeviceContext()->IASetInputLayout(m_manager->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_vertexlayout);

	//シェーダ設定
	renderer->GetDeviceContext()->VSSetShader(m_manager->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_vertexshader, NULL, 0);
	renderer->GetDeviceContext()->PSSetShader(m_manager->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_pixelshader, NULL, 0);


	//マトリクス設定
	DXMatrix world;
	world.SetTransform(m_position, m_rotation, m_scale);
	renderer->SetWorldMatrix(&world.GetMatrix());

	m_manager->GetModel(model_index)->Draw();
}

