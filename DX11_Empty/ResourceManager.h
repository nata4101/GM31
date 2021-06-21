#pragma once
#include "model.h"
#include <list>
#include <string>
#include "Singleton.h"


using namespace std;

class CResourceManager : public Singleton<CResourceManager>
{
public:
	CResourceManager(){}
	~CResourceManager(){}

	struct ModelPac
	{
		UINT model_index;
		const char* file_name;
		Model* model;
	};

	struct TexturePac
	{
		UINT texture_index;
		const char* file_name;
		ID3D11ShaderResourceView* texture;
	};

	struct ShaderPac
	{
		
		ID3D11VertexShader* m_vertexshader = NULL;
		ID3D11PixelShader* m_pixelshader = NULL;
		ID3D11InputLayout* m_vertexlayout = NULL;
	};

	enum ShaderList
	{
		TWODSHADER,
		THREEDSHADER,
		SHADERMAX
	};
	void Init(void);

	UINT LoadModelPac(const char* file_name);
	UINT LoadTexturePac(const char* file_name);

	Model* GetModel(UINT index);

	ID3D11ShaderResourceView* GetTexture(UINT index);

	void UnloadModelPac(UINT index);

	void UnloadModelPacAll(void);

	void UnloadTexturePac(UINT index);

	void UnloadTexturePacAll(void);

	ShaderPac* GetShaderPac(ShaderList shader) {
		return &shader_pac[shader];
	}

private:

	list<ModelPac*> model_list;
	list<TexturePac*> texture_list;

	ShaderPac shader_pac[SHADERMAX];

	UINT resource_count;
};

