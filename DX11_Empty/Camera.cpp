#include "main.h"
#include "renderer.h"
#include "Camera.h"

void CCamera::Init()
{
	m_position = D3DXVECTOR3(0, 2, -5);
	m_target = D3DXVECTOR3(0, 0, 0);
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
	D3DXMATRIX viewMatirx;
	D3DXMatrixLookAtLH(&viewMatirx, &m_position, &m_target, &D3DXVECTOR3(0, 1, 0));

	Renderer::SetViewMatrix(&viewMatirx);

	//プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1, 1000);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}
