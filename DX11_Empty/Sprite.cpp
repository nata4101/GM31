#include "GameObject.h"
#include "main.h"
#include "renderer.h"
#include "ResourceManager.h"
#include "Sprite.h"


void CSprite::Init()
{
	Renderer* render = Renderer::GetInstance();

	VERTEX_3D vertex[4];

	vertex[0].Position	= XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= XMFLOAT2(0.0f, 0.0f);
				
	vertex[1].Position	= XMFLOAT3(0.5f, -0.5f, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	= XMFLOAT2(1.0f, 0.0f);
					
	vertex[2].Position	= XMFLOAT3(-0.5f, 0.5f, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	= XMFLOAT2(0.0f, 1.0f);
				
	vertex[3].Position	= XMFLOAT3(0.5f, 0.5f, 0.0f);
	vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	= XMFLOAT2(1.0f, 1.0f);

	

	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	render->GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void CSprite::Uninit()
{
	m_VertexBuffer->Release();
}

void CSprite::Update()
{
}

void CSprite::Draw()
{
	Renderer* render = Renderer::GetInstance();
	CResourceManager* m_manager = CResourceManager::GetInstance();

	//���̓��C�A�E�g�ݒ�
	render->GetDeviceContext()->IASetInputLayout(m_manager->GetShaderPac(CResourceManager::ShaderList::TWODSHADER)->m_vertexlayout);

	//�V�F�[�_�ݒ�
	render->GetDeviceContext()->VSSetShader(m_manager->GetShaderPac(CResourceManager::ShaderList::TWODSHADER)->m_vertexshader, NULL, 0);
	render->GetDeviceContext()->PSSetShader(m_manager->GetShaderPac(CResourceManager::ShaderList::TWODSHADER)->m_pixelshader, NULL, 0);

	//�}�g���N�X�ݒ�
	render->SetWorldViewProjection2D();

	//�}�g���N�X�ݒ�
	DXMatrix world, scale, rot, trans;
	scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	rot =  XMMatrixRotationZ(m_rotation.z);
	trans =  XMMatrixTranslation(m_position.x + SCREEN_WIDTH / 2, m_position.y + SCREEN_HEIGHT / 2, m_position.z);
	world = scale * rot*trans;

	render->SetWorldMatrix(&world.GetMatrix());

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	render->GetDeviceContext()->IASetVertexBuffers(
		0, 1,
		&m_VertexBuffer,
		&stride,
		&offset);

	ID3D11ShaderResourceView*	m_Texture = m_manager->GetTexture(texture_index);
	//�e�N�X�`���ݒ�
	render->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	render->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	render->GetDeviceContext()->Draw(4, 0);
}

void CSprite::SetResource(const char * file_name)
{
	CResourceManager* resource = CResourceManager::GetInstance();

	texture_index = resource->LoadTexturePac(file_name);
}
