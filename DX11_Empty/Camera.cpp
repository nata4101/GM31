#include "main.h"
#include "renderer.h"
#include "Camera.h"

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
