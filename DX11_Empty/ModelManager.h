#pragma once
#include "model.h"
#include <list>
#include <string>


using namespace std;

class CModelManager
{
public:
	CModelManager(){}
	~CModelManager(){}

	struct ModelPac
	{
		string model_name;

		Model* model;


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

	static void LoadModelPac(string* model_name, const char* file_name);

	static Model* GetModel(string* name);

	static void UnloadModelPac(string* name);

	static void UnloadModelPacAll(void);

	static ShaderPac* GetShaderPac(ShaderList shader) {
		return &shader_pac[shader];
	}

private:

	static list<ModelPac*> model_list;

	static ShaderPac shader_pac[SHADERMAX];
};

