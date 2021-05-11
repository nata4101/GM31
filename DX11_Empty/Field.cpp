#include "main.h"
#include "renderer.h"
#include "Field.h"

using namespace DirectX;

void CField::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position	 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal	 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	 = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	 = XMFLOAT2(0.0f, 0.0f);
						
	vertex[1].Position	 = XMFLOAT3(200.0f, 0.0f, 0.0f);
	vertex[1].Normal	 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	 = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	 = XMFLOAT2(1.0f, 0.0f);
						 
	vertex[2].Position	 = XMFLOAT3(0.0f, 200.0f, 0.0f);
	vertex[2].Normal	 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	 = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	 = XMFLOAT2(0.0f, 1.0f);
					
	vertex[3].Position	 = XMFLOAT3(200.0f, 200.0f, 0.0f);
	vertex[3].Normal	 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	 = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	 = XMFLOAT2(1.0f, 1.0f);

	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset/texture/field004.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);

	Renderer::CreateVertexShader(
		&m_VertexShader,
		&m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_position	 = XMFLOAT3(0, 0, 0);
	m_rotation	 = XMFLOAT3(0, 0, 0);
	m_scale		 = XMFLOAT3(1, 1, 1);
}

void CField::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void CField::Update()
{
}

void CField::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_rotation.z, m_rotation.x, m_rotation.y);
	trans = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	world = scale * rot * trans;

	D3DXMATRIX buff;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			buff.m[i][j] = world.r[i].m128_f32[j];
		}
	}

	Renderer::SetWorldMatrix(&buff);

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(
		0, 1,
		&m_VertexBuffer,
		&stride,
		&offset);

	//�}�e���A���ݒ�
	MATERIAL material{};
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	Renderer::SetMaterial(material);

	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);
}
