#include "main.h"
#include "renderer.h"
#include "model.h"
#include "Player.h"
#include "input.h"
#include "Scene.h"
#include "manager.h"
#include "ModelManager.h"

void CPlayer::Init()
{
	CModelManager::LoadModelPac(&model_name, "asset\\model\\test\\test.obj");

	m_position = D3DXVECTOR3(0, 0, 0);
	m_rotation = D3DXVECTOR3(0, 0, 0);
	m_scale = D3DXVECTOR3(1, 1, 1);
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
		scene->AddGameObject<CBullet>()->SetPosition(m_position);
	}
}

void CPlayer::Draw()
{
	Renderer* renderer = Renderer::GetInstance();
	//入力レイアウト設定
	renderer->GetDeviceContext()->IASetInputLayout(CModelManager::GetShaderPac(CModelManager::ShaderList::THREEDSHADER)->m_vertexlayout);

	//シェーダ設定
	renderer->GetDeviceContext()->VSSetShader(CModelManager::GetShaderPac(CModelManager::ShaderList::THREEDSHADER)->m_vertexshader, NULL, 0);
	renderer->GetDeviceContext()->PSSetShader(CModelManager::GetShaderPac(CModelManager::ShaderList::THREEDSHADER)->m_pixelshader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_rotation.y, m_rotation.x, m_rotation.z);
	D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
	world = scale * rot*trans;
	renderer->SetWorldMatrix(&world);

	CModelManager::GetModel(&model_name)->Draw();
}
