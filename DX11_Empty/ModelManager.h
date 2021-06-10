#pragma once
#include "model.h"
#include <list>
#include <string>
#include "Singleton.h"


using namespace std;

class CModelManager : public Singleton<CModelManager>
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

	void LoadModelPac(string* model_name, const char* file_name);

	Model* GetModel(string* name);

	void UnloadModelPac(string* name);

	void UnloadModelPacAll(void);

	ShaderPac* GetShaderPac(ShaderList shader) {
		return &shader_pac[shader];
	}

private:

	list<ModelPac*> model_list;

	ShaderPac shader_pac[SHADERMAX];
};

