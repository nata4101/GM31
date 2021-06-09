#include "Enemy.h"
#include "renderer.h"
#include "ModelManager.h"

void CEnemy::Init()
{
	CModelManager::LoadModelPac(&m_model_name, "asset\\model\\torus\\torus.obj");

	m_position = D3DXVECTOR3(0, 0, 0);
	m_rotation = D3DXVECTOR3(0, 0, 0);
	m_scale = D3DXVECTOR3(1, 1, 1);
}

void CEnemy::Uninit()
{
}

void CEnemy::Update()
{
}

void CEnemy::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(CModelManager::GetShaderPac(CModelManager::ShaderList::THREEDSHADER)->m_vertexlayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(CModelManager::GetShaderPac(CModelManager::ShaderList::THREEDSHADER)->m_vertexshader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(CModelManager::GetShaderPac(CModelManager::ShaderList::THREEDSHADER)->m_pixelshader, NULL, 0);

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_rotation.y, m_rotation.x, m_rotation.z);
	D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
	world = scale * rot*trans;
	Renderer::SetWorldMatrix(&world);

	CModelManager::GetModel(&m_model_name)->Draw();
}

