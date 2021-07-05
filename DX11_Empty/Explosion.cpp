#include "Explosion.h"
#include "main.h"
#include "renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "manager.h"


UINT CExplosion::texture_index;

void CExplosion::Init()
{
	Renderer* renderer = Renderer::GetInstance();
	CResourceManager* resource = CResourceManager::GetInstance();
	texture_index = resource->LoadTexturePac("asset/texture/explosion.png");

	VERTEX_3D vertex[4];

	vertex[0].Position	= XMFLOAT3(-10.0f, 10.0f, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= XMFLOAT2(0.0f, 0.0f);
			
	vertex[1].Position	= XMFLOAT3(10.0f, 10.0f, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	= XMFLOAT2(1.0f, 0.0f);
			
	vertex[2].Position	= XMFLOAT3(-10.0f, -10.0f, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	= XMFLOAT2(0.0f, 1.0f);
			
	vertex[3].Position	= XMFLOAT3(10.0f, -10.0f, 0.0f);
	vertex[3].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	= XMFLOAT2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	renderer->GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_position	= XMFLOAT3(0, 0, 0);
	m_rotation	= XMFLOAT3(0, 0, 0);
	m_scale		= XMFLOAT3(1, 1, 1);
}

void CExplosion::Uninit()
{
}

void CExplosion::Update()
{
}

void CExplosion::Draw()
{
	CResourceManager* resource = CResourceManager::GetInstance();
	Renderer* renderer = Renderer::GetInstance();
	//入力レイアウト設定
	renderer->GetDeviceContext()->IASetInputLayout(resource->GetShaderPac(CResourceManager::TWODSHADER)->m_vertexlayout);

	//シェーダ設定
	renderer->GetDeviceContext()->VSSetShader(resource->GetShaderPac(CResourceManager::TWODSHADER)->m_vertexshader, NULL, 0);
	renderer->GetDeviceContext()->PSSetShader(resource->GetShaderPac(CResourceManager::TWODSHADER)->m_pixelshader, NULL, 0);

	CScene* scene = Manager::GetInstance()->GetScene();
	CCamera* camera = scene->GetGameObject<CCamera>();
	DXMatrix view = camera->GetViewMatrix();
	//ビューの逆行列
	DXMatrix invView;
	invView = XMMatrixInverse(nullptr, view.GetMatrix());
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;
	//マトリクス設定
	DXMatrix world, scale, rot, trans;
	scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	rot = XMMatrixRotationZ(m_rotation.z);
	trans = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	world = scale * rot * invView * trans;
	renderer->SetWorldMatrix(&world.GetMatrix());

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	renderer->GetDeviceContext()->IASetVertexBuffers(
		0, 1,
		&m_VertexBuffer,
		&stride,
		&offset);

	//マテリアル設定
	MATERIAL material{};
	ZeroMemory(&material, sizeof(MATERIAL));
	material.Diffuse = DXVector4(1, 1, 1, 1);
	renderer->SetMaterial(material);
	ID3D11ShaderResourceView*	m_Texture = resource->GetTexture(texture_index);
	//テクスチャ設定
	renderer->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ設定
	renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	renderer->GetDeviceContext()->Draw(4, 0);
}
