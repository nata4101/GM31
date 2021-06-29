#pragma once

#include "main.h"

using namespace DirectX;

class DXMatrix : public XMFLOAT4X4
{
public:
	DXMatrix(XMMATRIX a){XMStoreFloat4x4(this, a); return; }
	DXMatrix() { XMStoreFloat4x4(this, XMMatrixIdentity()); return; }
	~DXMatrix(){}

	DXMatrix operator+ (DXMatrix a) 
	{ 
		DXMatrix buff; 
		XMStoreFloat4x4(&buff, XMLoadFloat4x4(this) + XMLoadFloat4x4(&a)); 
		return buff; 
	}
	
	DXMatrix operator- (DXMatrix a)
	{
		DXMatrix buff;
		XMStoreFloat4x4(&buff, XMLoadFloat4x4(this) - XMLoadFloat4x4(&a));
		return buff;
	}

	DXMatrix operator* (DXMatrix a)
	{
		DXMatrix buff;
		XMStoreFloat4x4(&buff, XMLoadFloat4x4(this) * XMLoadFloat4x4(&a));
		return buff;
	}

	void operator+= (DXMatrix a)
	{
		XMStoreFloat4x4(this, XMLoadFloat4x4(this) + XMLoadFloat4x4(&a));
		return;
	}

	void operator-= (DXMatrix a)
	{
		XMStoreFloat4x4(this, XMLoadFloat4x4(this) - XMLoadFloat4x4(&a));
		return;
	}

	void operator*= (DXMatrix a)
	{
		XMStoreFloat4x4(this, XMLoadFloat4x4(this) * XMLoadFloat4x4(&a));
		return;
	}

	void operator= (XMMATRIX a)
	{
		XMStoreFloat4x4(this, a);
		return;
	}

	XMMATRIX GetMatrix(void) { return XMLoadFloat4x4(this); }


private:

};


