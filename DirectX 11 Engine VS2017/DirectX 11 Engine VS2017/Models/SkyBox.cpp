#include "SkyBox.h"



SkyBox::SkyBox() {}


bool SkyBox::Initialize(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation) {
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

		Vertex(-0.5f,  -0.5f, -0.5f, 0.0f, 1.0f), //FRONT Bottom Left   - [8]
		Vertex(-0.5f,   0.5f, -0.5f, 0.0f, 0.0f), //FRONT Top Left      - [9]
		Vertex(-0.5f,   0.5f, 0.5f, 1.0f, 0.0f), //BACK Top Left     - [10]
		Vertex(-0.5f,  -0.5f, 0.5f, 1.0f, 1.0f), //BACK Bottom Left   - [11]

		Vertex(0.5f,  -0.5f, -0.5f, 0.0f, 1.0f), //FRONT Bottom Right   - [12]
		Vertex(0.5f,   0.5f, -0.5f, 0.0f, 0.0f), //FRONT Top Right      - [13]
		Vertex(0.5f,   0.5f, 0.5f, 1.0f, 0.0f), //BACK Top Right     - [14]
		Vertex(0.5f,  -0.5f, 0.5f, 1.0f, 1.0f), //BACK Bottom Right   - [15]

		Vertex(-0.5f,  -0.5f, -0.5f, 0.0f, 1.0f), //FRONT Bottom Left   - [16]
		Vertex(-0.5f,   -0.5f, 0.5f, 0.0f, 0.0f), //BACK Bottom Left      - [17]
		Vertex(0.5f,   -0.5f, 0.5f, 1.0f, 0.0f), //BACK Bottom Right     - [18]
		Vertex(0.5f,  -0.5f, -0.5f, 1.0f, 1.0f), //FRONT Bottom Right   - [19]

		Vertex(-0.5f,  0.5f, 0.5f, 0.0f, 1.0f), //BACK Top Left   - [20]
		Vertex(-0.5f,   0.5f, -0.5f, 0.0f, 0.0f), //FRONT Top Left      - [21]
		Vertex(0.5f,   0.5f, -0.5f, 1.0f, 0.0f), //FRONT Top Right     - [22]
		Vertex(0.5f,  0.5f, 0.5f, 1.0f, 1.0f), //BACK Top Right   - [23]
	};

	std::vector<DWORD> indices =
	{
		2, 1, 0, //FRONT
		3, 2, 0, //FRONT

		6, 7, 4, //BACK 
		5, 6, 4, //BACK

		12, 14, 13, //RIGHT SIDE
		12, 15, 14, //RIGHT SIDE

		8, 10, 11, //LEFT SIDE
		9, 10, 8, //LEFT SIDE

		20, 21, 22, //TOP
		23, 20, 22, //TOP

		19, 16, 17, //BOTTOM
		19, 17, 18, //BOTTOM
	};


	if (!this->InitializeHelper(pDevice, pDeviceContext, L"Data\\Textures\\sky.jpg", v, indices, pos, rotation)) {
		return false;
	}

	return true;
}


SkyBox::~SkyBox() {}
