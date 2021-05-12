#include "main.h"
#include "renderer.h"
#include "Camera.h"

using namespace DirectX;

void CCamera::Init()
{
	m_position = XMVectorSet(0, 2, -5,0);
	m_target = XMVectorSet(0, 0, 0, 0);
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
	XMMATRIX view_matrix;
	view_matrix = XMMatrixLookAtLH(m_position, m_target, XMVectorSet(0, 1, 0, 0));


	Renderer::SetViewMatrix(&view_matrix);

	//プロジェクションマトリクス設定
	XMMATRIX projection_matrix;
	projection_matrix = XMMatrixPerspectiveFovLH(1, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1, 1000);

	Renderer::SetProjectionMatrix(&projection_matrix);
}
