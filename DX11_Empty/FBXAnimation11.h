#pragma once
#include "main.h"
#include "renderer.h"

class CFbxMesh
{
public:


private:
	int m_polygonCount;
	int m_vertexCount;
	int m_indexCount;
	int m_materialIndex;
	DXMatrix m_mtxLocal;
	VERTEX_3D* vertex;
	WORD* m_vertexIndex;
	ID3D11Buffer*	m_vertexBuffer;
	ID3D11Buffer*	m_indexBuffer;
};


class CFbxAnimation
{
public:

private:
	int m_meshCount;
	int m_materialCount;
	int m_animationFlame;
	int m_nowFlame;
	UINT m_textureIndex;
	MATERIAL* m_materials;
	CFbxMesh* m_meshes;
};
