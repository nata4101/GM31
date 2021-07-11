#include "main.h"
#include "renderer.h"
#include "model.h"
#include "Player.h"
#include "CBulet.h"
#include "input.h"
#include "Scene.h"
#include "manager.h"
#include "FBXAnimation11.h"
#include "ResourceManager.h"

UINT  CPlayer::model_index;
CFbxAnimation anime;

void CPlayer::Init()
{
	model_index = CResourceManager::GetInstance()->LoadModelPac("asset\\model\\test\\test.obj");

	m_position	= XMFLOAT3(0, 0, 0);
	m_rotation	= XMFLOAT3(0, 0, 0);
	m_scale		= XMFLOAT3(1, 1, 1);

	anime.Load("asset\model\AgWalk.mfa");
}

void CPlayer::Uninit()
{
}

void CPlayer::Update()
{
	Manager* manager = Manager::GetInstance();
	if (Input::GetKeyPress('A')) {
		m_rotation.y -= 0.05f;
	}
	if (Input::GetKeyPress('D')) {
		m_rotation.y += 0.05f;
	}
	if (Input::GetKeyPress('S')) {
		m_position -= GetForward() * 0.1f;
	}
	if (Input::GetKeyPress('W')) {
		m_position += GetForward() * 0.1f;
	}
	if (Input::GetKeyTrigger(VK_SPACE)) {
		CScene* scene = manager->GetScene();
		CBullet* bullet;
		bullet = scene->AddGameObject<CBullet>(CScene::THREED_OBJECT);
		bullet->SetPosition(m_position);
		bullet->SetDirection(GetForward());
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
