#include "Cube.h"



Cube::Cube() {}

bool Cube::Initialize(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation) {
	//Textured Square
	std::vector<Vertex> v =
	{
		Vertex(-0.5f,  -0.5f, -0.5f, 0.0f, 1.0f), //FRONT Bottom Left   - [0]
		Vertex(-0.5f,   0.5f, -0.5f, 0.0f, 0.0f), //FRONT Top Left      - [1]
		Vertex(0.5f,   0.5f, -0.5f, 1.0f, 0.0f), //FRONT Top Right     - [2]
		Vertex(0.5f,  -0.5f, -0.5f, 1.0f, 1.0f), //FRONT Bottom Right   - [3]
		Vertex(-0.5f,  -0.5f, 0.5f, 0.0f, 1.0f), //BACK Bottom Left   - [4]
		Vertex(-0.5f,   0.5f, 0.5f, 0.0f, 0.0f), //BACK Top Left      - [5]
		Vertex(0.5f,   0.5f, 0.5f, 1.0f, 0.0f), //BACK Top Right     - [6]
		Vertex(0.5f,  -0.5f, 0.5f, 1.0f, 1.0f), //BACK Bottom Right   - [7]
	};

	std::vector<DWORD> indices =
	{
		0, 1, 2, //FRONT
		0, 2, 3, //FRONT
		4, 7, 6, //BACK 
		4, 6, 5, //BACK
		3, 2, 6, //RIGHT SIDE
		3, 6, 7, //RIGHT SIDE
		4, 5, 1, //LEFT SIDE
		4, 1, 0, //LEFT SIDE
		1, 5, 6, //TOP
		1, 6, 2, //TOP
		0, 3, 7, //BOTTOM
		0, 7, 4, //BOTTOM
	};

	if (!this->InitializeHelper(pDevice, pDeviceContext, L"Data\\Textures\\piano.PNG", v, indices, pos, rotation)) {
		return false;
	}

	return true;
}

void Cube::Tick(double delta) {
	this->RotateRight(delta / 10);
}

Cube::~Cube() {}
