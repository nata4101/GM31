#include "CBulet.h"
#include "renderer.h"
#include "ModelManager.h"
#include "Scene.h"
#include "manager.h"

void CBullet::Init()
{
	CModelManager::LoadModelPac(&m_model_name, "asset\\model\\sphere\\sphere.obj");

	m_position = D3DXVECTOR3(0, 1, 0);
	m_rotation = D3DXVECTOR3(0, 0, 0);
	m_scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	dir = D3DXVECTOR3(0, 0, 1);
	speed = 0.1;
}

void CBullet::Uninit()
{
}

void CBullet::Update()
{
	m_position += dir * speed;

	CScene* scene = Manager::GetScene();
	std::vector<CEnemy*> enemy_list = scene->GetGameObjects<CEnemy>();

	for (CEnemy* enemy : enemy_list) {
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();

		D3DXVECTOR3 length = enemyPosition - m_position;
		if (2.0f > D3DXVec3Length(&length)) {
			enemy->SetDestroy();
			SetDestroy();
		}
	}

	if (m_position.z >= 10) {
		SetDestroy();
	}
}

void CBullet::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(CModelManager::GetShaderPac(CModelManager::ShaderList::THREEDSHADER)->m_vertexlayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(CModelManager::GetShaderPac(CModelManager::ShaderList::THREEDSHADER)->m_vertexshader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(CModelManager::GetShaderPac(CModelManager::ShaderList::THREEDSHADER)->m_pixelshader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_rotation.y, m_rotation.x, m_rotation.z);
	D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
	world = scale * rot*trans;
	Renderer::SetWorldMatrix(&world);

	CModelManager::GetModel(&m_model_name)->Draw();
}
