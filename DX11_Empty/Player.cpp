#include "main.h"
#include "renderer.h"
#include "model.h"
#include "Player.h"
#include "input.h"
#include "Scene.h"
#include "manager.h"
#include "ResourceManager.h"

UINT  CPlayer::model_index;

void CPlayer::Init()
{
	model_index = CResourceManager::GetInstance()->LoadModelPac("asset\\model\\test\\test.obj");

	m_position	= XMFLOAT3(0, 0, 0);
	m_rotation	= XMFLOAT3(0, 0, 0);
	m_scale		= XMFLOAT3(1, 1, 1);
}

void CPlayer::Uninit()
{
}

void CPlayer::Update()
{
	Manager* manager = Manager::GetInstance();
	if (Input::GetKeyPress('A')) {
		m_position.x -= 0.1f;
	}
	if (Input::GetKeyPress('D')) {
		m_position.x += 0.1f;
	}
	if (Input::GetKeyPress('S')) {
		m_position.z -= 0.1f;
	}
	if (Input::GetKeyPress('W')) {
		m_position.z += 0.1f;
	}
	if (Input::GetKeyTrigger(VK_SPACE)) {
		CScene* scene = manager->GetScene();
		scene->AddGameObject<CBullet>(CScene::THREED_OBJECT)->SetPosition(m_position);
	}
}

void CPlayer::Draw()
{
	CResourceManager* m_manager = CResourceManager::GetInstance();
	Renderer* renderer = Renderer::GetInstance();
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
