#pragma once
#include <DirectXMath.h>

struct CB_VS_vertexshader
{
	DirectX::XMMATRIX wpvMatrix;
	DirectX::XMMATRIX worldMatrix;
};

struct CB_PS_ambientLight
{
	DirectX::XMFLOAT3	ambientLightColor;
	float				ambientLightStrength;
};

struct CB_PS_dynamicLight {
	DirectX::XMFLOAT3	dynamicLightColor;
	float				dynamicLightStrength;
	DirectX::XMFLOAT3	dynamicLightPosition;
};