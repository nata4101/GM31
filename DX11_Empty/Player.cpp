#include "main.h"
#include "renderer.h"
#include "model.h"
#include "Player.h"
#include "input.h"
#include "Scene.h"
#include "manager.h"

void CPlayer::Init()
{
	m_model = new Model();
	m_model->Load("asset\\model\\test\\test.obj");

	Renderer::CreateVertexShader(
		&m_vertexshader,
		&m_vertexlayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_pixelshader, "vertexLightingPS.cso");

	m_position = D3DXVECTOR3(0, 0.5, 0);
	m_rotation = D3DXVECTOR3(0, 0, 0);
	m_scale = D3DXVECTOR3(1, 1, 1);
}

void CPlayer::Uninit()
{
	m_model->Unload();

	m_vertexlayout->Release();
	m_vertexshader->Release();
	m_pixelshader->Release();

	delete m_model;
}

void CPlayer::Update()
{
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
		CScene* scene = Manager::GetScene();
		scene->AddGameObject<CBullet>()->SetPosition(m_position);
	}
}

void CPlayer::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_vertexlayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_vertexshader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_pixelshader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_rotation.y, m_rotation.x, m_rotation.z);
	D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
	world = scale * rot*trans;
	Renderer::SetWorldMatrix(&world);

	m_model->Draw();
}
