#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "ResourceManager.h"

void CPolygon2D::Init()
{
	Renderer* render = Renderer::GetInstance();

	VERTEX_3D vertex[4];

	vertex[0].Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position	= D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	vertex[1].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	= D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position	= D3DXVECTOR3(0.0f, 200.0f, 0.0f);
	vertex[2].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	= D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position	= D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	vertex[3].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	= D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	render->GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		render->GetDevice(),
		"asset/texture/field004.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);

}

void CPolygon2D::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

}

void CPolygon2D::Update()
{
}

void CPolygon2D::Draw()
{
	Renderer* render = Renderer::GetInstance();
	CResourceManager* m_manager = CResourceManager::GetInstance();

	//入力レイアウト設定
	render->GetDeviceContext()->IASetInputLayout(m_manager->GetShaderPac(CResourceManager::ShaderList::TWODSHADER)->m_vertexlayout);

	//シェーダ設定
	render->GetDeviceContext()->VSSetShader(m_manager->GetShaderPac(CResourceManager::ShaderList::TWODSHADER)->m_vertexshader, NULL, 0);
	render->GetDeviceContext()->PSSetShader(m_manager->GetShaderPac(CResourceManager::ShaderList::TWODSHADER)->m_pixelshader, NULL, 0);

	//マトリクス設定
	render->SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	render->GetDeviceContext()->IASetVertexBuffers(
		0, 1,
		&m_VertexBuffer,
		&stride,
		&offset);

	//テクスチャ設定
	render->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ設定
	render->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	render->GetDeviceContext()->Draw(4,0);

}
