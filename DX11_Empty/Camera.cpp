#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Scene.h"
#include "Camera.h"
#include "input.h"
#include "Player.h"

void CCamera::Init()
{
	m_position = D3DXVECTOR3(0, 4, -5);
	m_target = D3DXVECTOR3(0, 0, 0);
}

void CCamera::Uninit()
{
}

void CCamera::Update()
{
	CPlayer* player = Manager::GetInstance()->GetScene()->GetGameObject<CPlayer>();

	m_target = player->GetPosition();

	//m_position = m_target + D3DXVECTOR3(0.0f, 5.0f, -8.0f);

	D3DXVECTOR3 forward = player->GetForward();
	m_position = m_target - forward * 5.0f + D3DXVECTOR3(0.0f, 3.0f, 0.0f);

	//if (Input::GetKeyPress(VK_LEFT)) {
	//	m_position.x -= 0.1f;
	//}
	//if (Input::GetKeyPress(VK_RIGHT)) {
	//	m_position.x += 0.1f;
	//}
	//if (Input::GetKeyPress(VK_DOWN)) {
	//	m_position.y -= 0.1f;
	//}
	//if (Input::GetKeyPress(VK_UP)) {
	//	m_position.y += 0.1f;
	//}
}

void CCamera::Draw()
{
	Renderer* renderer = Renderer::GetInstance();
	//ビューマトリクス設定
	D3DXMatrixLookAtLH(&m_viewMatirx, &m_position, &m_target, &D3DXVECTOR3(0, 1, 0));

	renderer->SetViewMatrix(&m_viewMatirx);

	//プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1, 1000);

	renderer->SetProjectionMatrix(&projectionMatrix);
}

D3DXMATRIX CCamera::GetViewMatrix()
{
	return m_viewMatirx;
}
