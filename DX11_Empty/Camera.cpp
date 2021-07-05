#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Scene.h"
#include "Camera.h"
#include "input.h"
#include "Player.h"

using namespace DirectX;

void CCamera::Init()
{
	m_position = *(new DXVector3(0, 2, -5));
	m_target = *(new DXVector3(0, 0, 0));
}

void CCamera::Uninit()
{
}

void CCamera::Update()
{
	CPlayer* player = Manager::GetInstance()->GetScene()->GetGameObject<CPlayer>();

	m_target = player->GetPosition();

	DXVector3 forward = player->GetForward();
	m_position = m_target - forward * 5.0f + DXVector3(0.0f, 3.0f, 0.0f);

}

void CCamera::Draw()
{
	//ビューマトリクス設定
	
	m_viewMatrix = XMMatrixLookAtLH(m_position.GetVector(), m_target.GetVector(), XMVectorSet(0, 1, 0, 0));


	Renderer::GetInstance()->SetViewMatrix(&m_viewMatrix.GetMatrix());

	//プロジェクションマトリクス設定
	XMMATRIX projection_matrix;
	projection_matrix = XMMatrixPerspectiveFovLH(1, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1, 1000);

	Renderer::GetInstance()->SetProjectionMatrix(&projection_matrix);
}
