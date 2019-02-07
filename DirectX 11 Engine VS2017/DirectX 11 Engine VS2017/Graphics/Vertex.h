#pragma once
#include <DirectXMath.h>

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz)
		: pos(x, y, z), texCoord(u, v), normal(nx, ny, nz) {}
	Vertex(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT2& uv, const DirectX::XMFLOAT3& normal)
		: pos(pos), texCoord(uv), normal(normal) {}
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 texCoord;
	DirectX::XMFLOAT3 normal;
};