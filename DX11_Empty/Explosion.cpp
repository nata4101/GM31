#include "Explosion.h"
#include "main.h"
#include "renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "manager.h"
#include "Camera.h"


UINT CExplosion::texture_index;

void CExplosion::Init()
{
	Renderer* renderer = Renderer::GetInstance();
	CResourceManager* resource = CResourceManager::GetInstance();
	texture_index = resource->LoadTexturePac("asset/texture/explosion.png");

	VERTEX_3D vertex[4];

	vertex[0].Position	= XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= XMFLOAT2(0.0f, 0.0f);
			
	vertex[1].Position	= XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	= XMFLOAT2(1.0f, 0.0f);
			
	vertex[2].Position	= XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	= XMFLOAT2(0.0f, 1.0f);
			
	vertex[3].Position	= XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	= XMFLOAT2(1.0f, 1.0f);

	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	renderer->GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_position	= XMFLOAT3(0, 0, 0);
	m_rotation	= XMFLOAT3(0, 0, 0);
	m_scale		= XMFLOAT3(2, 2, 1);

	m_count = 0;
}

void CExplosion::Uninit()
{
}

void CExplosion::Update()
{
	m_count += 0.2f;

	if (m_count > 15) {
		SetDestroy();
	}
}

void CExplosion::Draw()
{
	CResourceManager* resource = CResourceManager::GetInstance();
	Renderer* renderer = Renderer::GetInstance();

	//���_�f�[�^��������
	D3D11_MAPPED_SUBRESOURCE msr;
	HRESULT hr  = renderer->GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	if (FAILED(hr)) {
		int c = 0;
	}
	
	int now = m_count;
	float x, y;

	x = (float)(now % 4) * 0.25f;
	y = (float)(now / 4) * 0.25f;

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position	= XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= XMFLOAT2(x, y);
					
	vertex[1].Position	= XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	= XMFLOAT2(x + 0.25, y);
				
	vertex[2].Position	= XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	= XMFLOAT2(x, y + 0.25);
				
	vertex[3].Position	= XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	= XMFLOAT2(x + 0.25, y + 0.25);

	renderer->GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//���̓��C�A�E�g�ݒ�
	renderer->GetDeviceContext()->IASetInputLayout(resource->GetShaderPac(CResourceManager::TWODSHADER)->m_vertexlayout);

	//�V�F�[�_�ݒ�
	renderer->GetDeviceContext()->VSSetShader(resource->GetShaderPac(CResourceManager::TWODSHADER)->m_vertexshader, NULL, 0);
	renderer->GetDeviceContext()->PSSetShader(resource->GetShaderPac(CResourceManager::TWODSHADER)->m_pixelshader, NULL, 0);

	CScene* scene = Manager::GetInstance()->GetScene();
	CCamera* camera = scene->GetGameObject<CCamera>();
	DXMatrix view = camera->GetViewMatrix();
	//�r���[�̋t�s��
	DXMatrix invView;
	invView = XMMatrixInverse(nullptr, view.GetMatrix());
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;
	//�}�g���N�X�ݒ�
	DXMatrix world, scale, rot, trans;
	scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	rot = XMMatrixRotationZ(m_rotation.z);
	trans = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	world = scale * rot * invView * trans;
	renderer->SetWorldMatrix(&world.GetMatrix());

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	renderer->GetDeviceContext()->IASetVertexBuffers(
		0, 1,
		&m_VertexBuffer,
		&stride,
		&offset);

	//�}�e���A���ݒ�
	MATERIAL material{};
	ZeroMemory(&material, sizeof(MATERIAL));
	material.Diffuse = DXVector4(1, 1, 1, 1);
	renderer->SetMaterial(material);
	ID3D11ShaderResourceView*	m_Texture = resource->GetTexture(texture_index);
	//�e�N�X�`���ݒ�
	renderer->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	renderer->GetDeviceContext()->Draw(4, 0);
}
