#include "main.h"
#include "renderer.h"
#include "ResourceManager.h"
#include "FBXAnimation11.h"

void CFbxAnimation::Load(const char * file_name)
{
	FILE* file;
	file = fopen(file_name, "rb");
	fread(&m_meshCount, sizeof(int), 1, file);
	fread(&m_animationFlame, sizeof(int), 1, file);
	fread(&m_materialCount, sizeof(int), 1, file);

	m_meshes = new CFbxMesh[m_meshCount];
	m_materials = new MATERIAL[m_materialCount];

	for (int i = 0; i < m_materialCount; i++) {
		float color[4];

		fread(color, sizeof(float), 4, file);
		m_materials[i].Diffuse = DXVector4(color[0], color[1], color[2], color[3]);
		
		fread(color, sizeof(float), 4, file);
		m_materials[i].Ambient = DXVector4(color[0], color[1], color[2], color[3]);

		fread(color, sizeof(float), 4, file);
		m_materials[i].Specular = DXVector4(color[0], color[1], color[2], color[3]);

		fread(color, sizeof(float), 4, file);
		m_materials[i].Emission = DXVector4(color[0], color[1], color[2], color[3]);

		fread(color, sizeof(float), 1, file);
		m_materials[i].Shininess = color[0];
	}

	for (int i = 0; i < m_meshCount; i++) {
		fread(&(m_meshes[i].m_materialIndex), sizeof(int), 1, file);
		fread(&(m_meshes[i].m_polygonCount), sizeof(int), 1, file);
		fread(&(m_meshes[i].m_vertexCount), sizeof(int), 1, file);
		fread(&(m_meshes[i].m_indexCount), sizeof(int), 1, file);
		m_meshes[i].m_mtxLocal = new DXMatrix[m_animationFlame];

		for (int j = 0; j < m_animationFlame; j++) {
			fread(&m_meshes[i].m_mtxLocal[j], sizeof(XMFLOAT4X4), 1, file);
		}

		m_meshes[i].m_vertex = new VERTEX_3D[m_meshes[i].m_vertexCount];
		m_meshes[i].m_vertexIndex = new WORD[m_meshes[i].m_indexCount];

		for (int j = 0; j < m_meshes[i].m_vertexCount; j++) {
			fread(&m_meshes[i].m_vertex[j].Position, sizeof(XMFLOAT3), 1, file);
			fread(&m_meshes[i].m_vertex[j].Normal, sizeof(XMFLOAT3), 1, file);
			DWORD color;
			fread(&color, sizeof(DWORD), 1, file);
			m_meshes[i].m_vertex[j].Diffuse.w = (color >> 24) & 0xff;
			m_meshes[i].m_vertex[j].Diffuse.w /= 255;
			m_meshes[i].m_vertex[j].Diffuse.x = (color >> 16) & 0xff;
			m_meshes[i].m_vertex[j].Diffuse.x /= 255;
			m_meshes[i].m_vertex[j].Diffuse.y = (color >> 8) & 0xff;
			m_meshes[i].m_vertex[j].Diffuse.y /= 255;
			m_meshes[i].m_vertex[j].Diffuse.z = (color) & 0xff;
			m_meshes[i].m_vertex[j].Diffuse.z /= 255;
			fread(&m_meshes[i].m_vertex[j].TexCoord, sizeof(XMFLOAT2), 1, file);

		}

		for (int j = 0; j < m_meshes[i].m_indexCount; j++) {
			fread(&m_meshes[i].m_vertexIndex[j], sizeof(WORD), 1, file);
		}
			
	}
	fclose(file);

	Renderer* renderer = Renderer::GetInstance();

	for (int i = 0; i < m_meshCount; i++) {
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * m_meshes[i].m_vertexCount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_meshes[i].m_vertex;

		renderer->GetDevice()->CreateBuffer(&bd, &sd, &(m_meshes[i].m_vertexBuffer));
		delete[] m_meshes[i].m_vertex;
	}

	for (int i = 0; i < m_meshCount; i++) {
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * m_meshes[i].m_indexCount;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_meshes[i].m_vertexIndex;

		renderer->GetDevice()->CreateBuffer(&bd, &sd, &(m_meshes[i].m_indexBuffer));
		delete[] m_meshes[i].m_vertexIndex;
	}
}

void CFbxAnimation::Draw(DXMatrix* mtx)
{
	Renderer* renderer = Renderer::GetInstance();
	CResourceManager* resource = CResourceManager::GetInstance();
	//入力レイアウト設定
	renderer->GetDeviceContext()->IASetInputLayout(resource->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_vertexlayout);

	//シェーダ設定
	renderer->GetDeviceContext()->VSSetShader(resource->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_vertexshader, NULL, 0);
	renderer->GetDeviceContext()->PSSetShader(resource->GetShaderPac(CResourceManager::ShaderList::THREEDSHADER)->m_pixelshader, NULL, 0);

	for (int i = 0; i < m_meshCount; i++) {
		m_meshes[i].Draw(m_nowFlame, m_materials, mtx, m_textureIndex);
	}
	m_nowFlame++;
	m_nowFlame %= m_animationFlame;
}

void CFbxAnimation::SetTexture(const char * file_name)
{
	CResourceManager* resource = CResourceManager::GetInstance();
	m_textureIndex = resource->LoadTexturePac(file_name);

}

void CFbxMesh::Draw(int flame, MATERIAL* mat, DXMatrix* mtx, int texture)
{
	Renderer* renderer = Renderer::GetInstance();
	CResourceManager* resource = CResourceManager::GetInstance();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	renderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	renderer->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// プリミティブトポロジ設定
	renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	MATERIAL material = {};
	material.Ambient = DXVector4(0.1,0.1,0.1,1);
	material.Diffuse = DXVector4(0.1, 0.1, 0.1,1);
	material.Emission = mat[m_materialIndex].Ambient + mat[m_materialIndex].Diffuse;

	renderer->SetMaterial(material);

	ID3D11ShaderResourceView* tex = resource->GetTexture(texture);

	renderer->GetDeviceContext()->PSSetShaderResources(0, 1, &tex);

	DXMatrix wld;

	wld = m_mtxLocal[flame] * *mtx;

	renderer->SetWorldMatrix(&wld.GetMatrix());

	renderer->GetDeviceContext()->DrawIndexed(m_indexCount, 0, 0);
}

