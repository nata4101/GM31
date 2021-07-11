#pragma once

class CFbxMesh
{
public:
	void Draw(int flame,MATERIAL* mat, DXMatrix* mtx,int texture);
	int m_polygonCount;
	int m_vertexCount;
	int m_indexCount;
	int m_materialIndex;
	DXMatrix* m_mtxLocal;
	VERTEX_3D* m_vertex;
	WORD* m_vertexIndex;
	ID3D11Buffer*	m_vertexBuffer;
	ID3D11Buffer*	m_indexBuffer;
};


class CFbxAnimation
{
public:
	CFbxAnimation() 
	{
		m_meshCount = 0;
		m_materialCount = 0;
		m_animationFlame = 0;
		m_nowFlame = 0;
		m_textureIndex = -1;
		m_materials = 0;
		m_meshes = 0;
	}

	~CFbxAnimation()
	{
		if (!m_materials) delete[] m_materials;
		if (!m_meshes) delete[] m_meshes;
	}
	void Load(const char* file_name);
	void Draw(DXMatrix* mtx);
	void SetTexture(const char* file_name);
	void SetFlame(int flame) { m_nowFlame = flame; }

private:
	int m_meshCount;
	int m_materialCount;
	int m_animationFlame;
	int m_nowFlame;
	int m_textureIndex;
	MATERIAL* m_materials;
	CFbxMesh* m_meshes;
};
