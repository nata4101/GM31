#pragma once
#include "Singleton.h"

using namespace DirectX;

struct VERTEX_3D
{
	DXVector3 Position;
	DXVector3 Normal;
    DXVector4 Diffuse;
	DXVector2 TexCoord;
};



struct MATERIAL
{
	DXVector4	Ambient;
	DXVector4	Diffuse;
	DXVector4	Specular;
	DXVector4	Emission;
	float		Shininess;
	float		Dummy[3];
};



struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	DXVector4	Direction;
	DXVector4	Diffuse;
	DXVector4	Ambient;
};



class Renderer : public Singleton<Renderer>
{
private:

	D3D_FEATURE_LEVEL       m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;;

	ID3D11Device*           m_Device;
	ID3D11DeviceContext*    m_DeviceContext;
	IDXGISwapChain*         m_SwapChain;
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11DepthStencilView* m_DepthStencilView;

	ID3D11Buffer*			m_WorldBuffer;
	ID3D11Buffer*			m_ViewBuffer;
	ID3D11Buffer*			m_ProjectionBuffer;
	ID3D11Buffer*			m_MaterialBuffer;
	ID3D11Buffer*			m_LightBuffer;


	ID3D11DepthStencilState* m_DepthStateEnable;
	ID3D11DepthStencilState* m_DepthStateDisable;




public:
	void Init();
	void Uninit();
	void Begin();
	void End();

	void SetDepthEnable(bool Enable);
	void SetWorldViewProjection2D();
	void SetWorldMatrix(XMMATRIX* WorldMatrix);
	void SetViewMatrix(XMMATRIX* ViewMatrix);
	void SetProjectionMatrix(XMMATRIX* ProjectionMatrix);
	void SetMaterial(MATERIAL Material);
	void SetLight(LIGHT Light);

	ID3D11Device* GetDevice( void ){ return m_Device; }
	ID3D11DeviceContext* GetDeviceContext( void ){ return m_DeviceContext; }



	void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);


};
