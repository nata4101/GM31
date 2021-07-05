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
	//���̓��C�A�E�g�ݒ�
	renderer->GetDeviceContext()->IASetInputLayout(m_manager->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_vertexlayout);

	//�V�F�[�_�ݒ�
	renderer->GetDeviceContext()->VSSetShader(m_manager->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_vertexshader, NULL, 0);
	renderer->GetDeviceContext()->PSSetShader(m_manager->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_pixelshader, NULL, 0);


	//�}�g���N�X�ݒ�
	DXMatrix world;
	world.SetTransform(m_position, m_rotation, m_scale);
	renderer->SetWorldMatrix(&world.GetMatrix());

	m_manager->GetModel(model_index)->Draw();
}

