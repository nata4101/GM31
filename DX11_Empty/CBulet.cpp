#include "CBulet.h"
#include "renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "manager.h"
#include "Enemy.h"
#include "Explosion.h"

UINT CBullet::model_index;

void CBullet::Init()
{
	model_index = CResourceManager::GetInstance()->LoadModelPac("asset\\model\\sphere\\sphere.obj");

	m_position = D3DXVECTOR3(0, 1, 0);
	m_rotation = D3DXVECTOR3(0, 0, 0);
	m_scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	dir = D3DXVECTOR3(0, 0, 1);
	speed = 0.2;
}

void CBullet::Uninit()
{
}

void CBullet::Update()
{
	m_position += dir * speed;

	Manager* manager = Manager::GetInstance();

	CScene* scene = manager->GetScene();
	std::vector<CEnemy*> enemy_list = scene->GetGameObjects<CEnemy>(CScene::THREED_OBJECT);

	for (CEnemy* enemy : enemy_list) {
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();

		D3DXVECTOR3 length = enemyPosition - m_position;
		if (2.0f > D3DXVec3Length(&length)) {
			enemy->SetDestroy();
			SetDestroy();
			scene->AddGameObject<CExplosion>(CScene::THREED_OBJECT)->SetPosition(enemyPosition);

		}
	}

	if (m_position.z >= 10) {
		SetDestroy();
	}
}

void CBullet::Draw()
{
	CResourceManager* m_manager = CResourceManager::GetInstance();
	Renderer* renderer = Renderer::GetInstance();
	//入力レイアウト設定
	renderer->GetDeviceContext()->IASetInputLayout(m_manager->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_vertexlayout);

	//シェーダ設定
	renderer->GetDeviceContext()->VSSetShader(m_manager->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_vertexshader, NULL, 0);
	renderer->GetDeviceContext()->PSSetShader(m_manager->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_pixelshader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_rotation.y, m_rotation.x, m_rotation.z);
	D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
	world = scale * rot*trans;
	renderer->SetWorldMatrix(&world);

	m_manager->GetModel(model_index)->Draw();
}
