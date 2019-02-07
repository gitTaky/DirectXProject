#include "Cube.h"



Cube::Cube() {}

bool Cube::Initialize(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation) {
	//Textured Square
	//Textured Square
	const XMFLOAT3 front_bottom_left_v(-0.5f, -0.5f, -0.5f);
	const XMFLOAT3 front_top_left_v(-0.5f, 0.5f, -0.5f);
	const XMFLOAT3 front_top_right_v(0.5f, 0.5f, -0.5f);
	const XMFLOAT3 front_bottom_right_v(0.5f, -0.5f, -0.5f);
	const XMFLOAT3 back_bottom_left_v(-0.5f, -0.5f, 0.5f);
	const XMFLOAT3 back_top_left_v(-0.5f, 0.5f, 0.5f);
	const XMFLOAT3 back_top_right_v(0.5f, 0.5f, 0.5f);
	const XMFLOAT3 back_bottom_right_v(0.5f, -0.5f, 0.5f);

	const XMFLOAT2 upper_left_uv(0.f, 0.f);
	const XMFLOAT2 lower_left_uv(0.f, 1.f);
	const XMFLOAT2 upper_right_uv(1.f, 0.f);
	const XMFLOAT2 lower_right_uv(1.f, 1.f);

	const XMFLOAT3 front_n(0.f, 0.f, -1.f);
	const XMFLOAT3 back_n(0.f, 0.f, 1.f);
	const XMFLOAT3 top_n(0.f, 1.f, 0.f);
	const XMFLOAT3 bottom_n(0.f, -1.f, 0.f);
	const XMFLOAT3 left_n(-1.f, 0.f, 0.f);
	const XMFLOAT3 right_n(1.f, 0.f, 0.f);

	std::vector<Vertex> v =
	{
		Vertex(front_bottom_left_v, lower_left_uv, front_n), //FRONT Bottom Left   - [0]
		Vertex(front_top_left_v, upper_right_uv, front_n), //FRONT Top Left      - [1]
		Vertex(front_top_right_v, upper_right_uv, front_n), //FRONT Top Right     - [2]
		Vertex(front_bottom_right_v, lower_right_uv, front_n), //FRONT Bottom Right   - [3]

		Vertex(back_bottom_left_v, lower_left_uv, back_n), //BACK Bottom Left   - [4]
		Vertex(back_top_left_v, upper_left_uv, back_n), //BACK Top Left      - [5]
		Vertex(back_top_right_v, upper_right_uv, back_n), //BACK Top Right     - [6]
		Vertex(back_bottom_right_v, lower_right_uv, back_n), //BACK Bottom Right   - [7]

		Vertex(front_bottom_left_v,lower_left_uv, left_n), //FRONT Bottom Left   - [8]
		Vertex(front_top_left_v, upper_left_uv, left_n), //FRONT Top Left      - [9]
		Vertex(back_top_left_v, upper_left_uv, left_n), //BACK Top Left     - [10]
		Vertex(back_bottom_left_v, lower_left_uv, left_n), //BACK Bottom Left   - [11]

		Vertex(front_bottom_right_v, lower_right_uv, right_n), //FRONT Bottom Right   - [12]
		Vertex(front_top_right_v, upper_right_uv, right_n), //FRONT Top Right      - [13]
		Vertex(back_top_right_v, upper_right_uv, right_n), //BACK Top Right     - [14]
		Vertex(back_bottom_right_v, lower_right_uv, right_n), //BACK Bottom Right   - [15]

		Vertex(front_bottom_left_v, lower_left_uv, bottom_n), //FRONT Bottom Left   - [16]
		Vertex(back_bottom_left_v, lower_left_uv, bottom_n), //BACK Bottom Left      - [17]
		Vertex(back_bottom_right_v, lower_right_uv, bottom_n), //BACK Bottom Right     - [18]
		Vertex(front_bottom_right_v, lower_right_uv, bottom_n), //FRONT Bottom Right   - [19]

		Vertex(back_top_left_v, upper_left_uv, top_n), //BACK Top Left   - [20]
		Vertex(front_top_left_v, upper_left_uv, top_n), //FRONT Top Left      - [21]
		Vertex(front_top_right_v, upper_right_uv, top_n), //FRONT Top Right     - [22]
		Vertex(back_top_right_v, upper_right_uv, top_n), //BACK Top Right   - [23]
	};

	std::vector<DWORD> indices =
	{
		0, 1, 2, //FRONT
		0, 2, 3, //FRONT

		4, 7, 6, //BACK 
		4, 6, 5, //BACK

		13, 14, 12, //RIGHT SIDE
		14, 15, 12, //RIGHT SIDE

		11, 10, 8, //LEFT SIDE
		8, 10, 9, //LEFT SIDE

		22, 21, 20, //TOP
		22, 20, 23, //TOP

		17, 16, 19, //BOTTOM
		18, 17, 19, //BOTTOM
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
