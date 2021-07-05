#include "main.h"
#include "renderer.h"
#include "polygon2D.h"

using namespace DirectX;

void CPolygon2D::Init()
{
	Renderer* renderer = Renderer::GetInstance();
	
	VERTEX_3D vertex[4];

	vertex[0].Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= XMFLOAT2(0.0f, 0.0f);
				
	vertex[1].Position	= XMFLOAT3(200.0f, 0.0f, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	= XMFLOAT2(1.0f, 0.0f);
					
	vertex[2].Position	= XMFLOAT3(0.0f, 200.0f, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	= XMFLOAT2(0.0f, 1.0f);
					
	vertex[3].Position	= XMFLOAT3(200.0f, 200.0f, 0.0f);
	vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
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

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		renderer->GetDevice(),
		"asset/texture/field004.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);

	renderer->CreateVertexShader(
		&m_VertexShader,
		&m_VertexLayout,
		"unlitTextureVS.cso");

	renderer->CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");
}

void CPolygon2D::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void CPolygon2D::Update()
{
}

void CPolygon2D::Draw()
{
	Renderer* renderer = Renderer::GetInstance();

	//入力レイアウト設定
	renderer->GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	renderer->GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	renderer->GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	renderer->SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	renderer->GetDeviceContext()->IASetVertexBuffers(
		0, 1,
		&m_VertexBuffer,
		&stride,
		&offset);

	//テクスチャ設定
	renderer->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ設定
	renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	renderer->GetDeviceContext()->Draw(4,0);

}
