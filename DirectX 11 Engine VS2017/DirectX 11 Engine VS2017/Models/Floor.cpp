#include "Floor.h"



Floor::Floor() {}


bool Floor::Initialize(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation) {
	//Textured Square
	std::vector<Vertex> v =
	{
		Vertex(-1.f,  0.f, -1.f, 0.0f, 1.0f, 0.f, 1.f, 0.f), //FRONT Bottom Left   - [0]
		Vertex(-1.f,   0.f, 1.f, 0.0f, 0.0f, 0.f, 1.f, 0.f), //FRONT Top Left      - [1]
		Vertex(1.f,   0.f, -1.f, 1.0f, 0.0f, 0.f, 1.f, 0.f), //FRONT Top Right     - [2]
		Vertex(1.f,  0.f, 1.f, 1.0f, 1.0f, 0.f, 1.f, 0.f), //FRONT Bottom Right   - [3]
	};

	std::vector<DWORD> indices =
	{
		0, 1, 2, //FRONT
		2, 1, 3, //FRONT
	};


	if (!this->InitializeHelper(pDevice, pDeviceContext, L"Data\\Textures\\pinksquare.jpg", v, indices, pos, rotation)) {
		return false;
	}

	return true;
}

Floor::~Floor() {}
