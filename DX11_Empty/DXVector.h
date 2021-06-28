#pragma once

#include "main.h"

using namespace DirectX;

class DXVector4 : public XMFLOAT4
{
public:
	DXVector4(){}
	DXVector4(XMFLOAT4 a) { x = a.x; y = a.y; z = a.z; w = a.w; }
	DXVector4(float ix,float iy,float iz,float iw){ x = ix; y = iy; z = iz; w = iw; }
	~DXVector4(){}

	DXVector4 operator+(DXVector4 a)
	{ 
		DXVector4 buff;
		XMStoreFloat4(&buff, XMLoadFloat4(this) + XMLoadFloat4(&a));
		return buff;
	}

	DXVector4 operator-(DXVector4 a)
	{
		DXVector4 buff;
		XMStoreFloat4(&buff, XMLoadFloat4(this) - XMLoadFloat4(&a));
		return buff;
	}

	DXVector4 operator/(DXVector4 a)
	{
		DXVector4 buff;
		XMStoreFloat4(&buff, XMLoadFloat4(this) / XMLoadFloat4(&a));
		return buff;
	}

	DXVector4 operator*(DXVector4 a)
	{
		DXVector4 buff;
		XMStoreFloat4(&buff, XMLoadFloat4(this) * XMLoadFloat4(&a));
		return buff;
	}

	void operator+=(DXVector4 a)
	{
		XMStoreFloat4(this, XMLoadFloat4(this) + XMLoadFloat4(&a));
		return;
	}

	void operator-=(DXVector4 a)
	{
		XMStoreFloat4(this, XMLoadFloat4(this) - XMLoadFloat4(&a));
		return;
	}

	void operator/=(DXVector4 a)
	{
		XMStoreFloat4(this, XMLoadFloat4(this) / XMLoadFloat4(&a));
		return;
	}

	void operator*=(DXVector4 a)
	{
		XMStoreFloat4(this, XMLoadFloat4(this) * XMLoadFloat4(&a));
		return;
	}

	DXVector4 operator/(float a)
	{
		DXVector4 buff;
		XMStoreFloat4(&buff, XMLoadFloat4(this) / a);
		return buff;
	}

	DXVector4 operator*(float a)
	{
		DXVector4 buff;
		XMStoreFloat4(&buff, XMLoadFloat4(this) * a);
		return buff;
	}

	void operator=(XMVECTOR a) { XMStoreFloat4(this, a); return; }
	
	XMVECTOR GetVector(void) { return XMLoadFloat4(this); }
	float GetLength(void) { return XMVectorGetX(XMVector4Length(XMLoadFloat4(this))); }
private:

};

class DXVector3 : public XMFLOAT3
{
public:
	DXVector3() {}
	DXVector3(XMFLOAT3 a) { x = a.x; y = a.y; z = a.z; }
	DXVector3(float ix, float iy, float iz) { x = ix; y = iy; z = iz; }
	~DXVector3() {}

	DXVector3 operator+(DXVector3 a)
	{
		DXVector3 buff;
		XMStoreFloat3(&buff, XMLoadFloat3(this) + XMLoadFloat3(&a));
		return buff;
	}

	DXVector3 operator-(DXVector3 a)
	{
		DXVector3 buff;
		XMStoreFloat3(&buff, XMLoadFloat3(this) - XMLoadFloat3(&a));
		return buff;
	}

	DXVector3 operator/(DXVector3 a)
	{
		DXVector3 buff;
		XMStoreFloat3(&buff, XMLoadFloat3(this) / XMLoadFloat3(&a));
		return buff;
	}

	DXVector3 operator*(DXVector3 a)
	{
		DXVector3 buff;
		XMStoreFloat3(&buff, XMLoadFloat3(this) * XMLoadFloat3(&a));
		return buff;
	}

	void operator+=(DXVector3 a)
	{
		XMStoreFloat3(this, XMLoadFloat3(this) + XMLoadFloat3(&a));
		return;
	}

	void operator-=(DXVector3 a)
	{
		XMStoreFloat3(this, XMLoadFloat3(this) - XMLoadFloat3(&a));
		return;
	}

	void operator/=(DXVector3 a)
	{
		XMStoreFloat3(this, XMLoadFloat3(this) / XMLoadFloat3(&a));
		return;
	}

	void operator*=(DXVector3 a)
	{
		XMStoreFloat3(this, XMLoadFloat3(this) * XMLoadFloat3(&a));
		return;
	}

	DXVector3 operator/(float a)
	{
		DXVector3 buff;
		XMStoreFloat3(&buff, XMLoadFloat3(this) / a);
		return buff;
	}

	DXVector3 operator*(float a)
	{
		DXVector3 buff;
		XMStoreFloat3(&buff, XMLoadFloat3(this) * a);
		return buff;
	}

	void operator=(XMVECTOR a) { XMStoreFloat3(this, a); return; }

	XMVECTOR GetVector(void) { return XMLoadFloat3(this); }

	float GetLength(void) { return XMVectorGetX(XMVector3Length(XMLoadFloat3(this))); }
private:

};

class DXVector2 : public XMFLOAT2
{
public:
	DXVector2() {}
	DXVector2(XMFLOAT2 a) { x = a.x; y = a.y; }
	DXVector2(float ix, float iy) { x = ix; y = iy; }
	~DXVector2() {}

	DXVector2 operator+(DXVector2 a)
	{
		DXVector2 buff;
		XMStoreFloat2(&buff, XMLoadFloat2(this) + XMLoadFloat2(&a));
		return buff;
	}

	DXVector2 operator-(DXVector2 a)
	{
		DXVector2 buff;
		XMStoreFloat2(&buff, XMLoadFloat2(this) - XMLoadFloat2(&a));
		return buff;
	}

	DXVector2 operator/(DXVector2 a)
	{
		DXVector2 buff;
		XMStoreFloat2(&buff, XMLoadFloat2(this) / XMLoadFloat2(&a));
		return buff;
	}

	DXVector2 operator*(DXVector2 a)
	{
		DXVector2 buff;
		XMStoreFloat2(&buff, XMLoadFloat2(this) * XMLoadFloat2(&a));
		return buff;
	}

	void operator+=(DXVector2 a)
	{
		XMStoreFloat2(this, XMLoadFloat2(this) + XMLoadFloat2(&a));
		return;
	}

	void operator-=(DXVector2 a)
	{
		XMStoreFloat2(this, XMLoadFloat2(this) - XMLoadFloat2(&a));
		return;
	}

	void operator/=(DXVector2 a)
	{
		XMStoreFloat2(this, XMLoadFloat2(this) / XMLoadFloat2(&a));
		return;
	}

	void operator*=(DXVector2 a)
	{
		XMStoreFloat2(this, XMLoadFloat2(this) * XMLoadFloat2(&a));
		return;
	}

	DXVector2 operator/(float a)
	{
		DXVector2 buff;
		XMStoreFloat2(&buff, XMLoadFloat2(this) / a);
		return buff;
	}

	DXVector2 operator*(float a)
	{
		DXVector2 buff;
		XMStoreFloat2(&buff, XMLoadFloat2(this) * a);
		return buff;
	}

	void operator=(XMVECTOR a) { XMStoreFloat2(this, a); return; }

	XMVECTOR GetVector(void) { return XMLoadFloat2(this); }

	float GetLength(void) { return XMVectorGetX(XMVector2Length(XMLoadFloat2(this))); }
private:

};
