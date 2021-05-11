#include "Camera.h"
#include "main.h"
#include "renderer.h"

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
	//�r���[�}�g���N�X�ݒ�
	XMMATRIX view_matrix;
	XMMatrixLookAtLH(m_position, m_target, XMVectorSet(0, 1, 0, 0));

	D3DXMATRIX buff;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			buff.m[i][j] = view_matrix.r[i].m128_f32[j];
		}
	}
	Renderer::SetViewMatrix(&buff);

	//�v���W�F�N�V�����}�g���N�X�ݒ�
	XMMATRIX projection_matrix;
	projection_matrix = XMMatrixPerspectiveFovLH(1, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1, 1000);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			buff.m[i][j] = view_matrix.r[i].m128_f32[j];
		}
	}

	Renderer::SetProjectionMatrix(&buff);
}
