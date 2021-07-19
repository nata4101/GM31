#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class DXQuaternion : public XMFLOAT4
{
public:
	DXQuaternion() { XMStoreFloat4(this, XMQuaternionIdentity()); }

	void operator=(XMVECTOR a) { XMStoreFloat4(this, a); return; }

	DXQuaternion operator*(DXQuaternion a)
	{
		DXQuaternion buff;
		XMStoreFloat4(&buff, XMQuaternionMultiply(this->GetVector(),a.GetVector()));
		return buff;
	}

	DXQuaternion operator*=(DXQuaternion a){ XMStoreFloat4(this, XMQuaternionMultiply(this->GetVector(), a.GetVector()));}
	XMVECTOR GetVector(void) { return XMLoadFloat4(this); }

	void CreateQuaternion(float x, float y, float z) { XMStoreFloat4(this, XMQuaternionRotationRollPitchYaw(x,y,z));}


private:

};

