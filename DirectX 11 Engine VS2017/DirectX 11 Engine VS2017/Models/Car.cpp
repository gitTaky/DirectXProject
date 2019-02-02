#include "Car.h"



Car::Car() {}

bool Car::Initialize(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation) {
	//Textured Square
	std::vector<Vertex> v =
	{
		Vertex(-0.5f,  -0.5f, -1.f, 0.0f, 1.0f), //FRONT Bottom Left   - [0]
		Vertex(-0.5f,   0.5f, -1.f, 0.0f, 0.0f), //FRONT Top Left      - [1]
		Vertex(0.5f,   0.5f, -1.f, 1.0f, 0.0f), //FRONT Top Right     - [2]
		Vertex(0.5f,  -0.5f, -1.f, 1.0f, 1.0f), //FRONT Bottom Right   - [3]

		Vertex(-0.5f,  -0.5f, 1.f, 0.0f, 1.0f), //BACK Bottom Left   - [4]
		Vertex(-0.5f,   0.5f, 1.f, 0.0f, 0.0f), //BACK Top Left      - [5]
		Vertex(0.5f,   0.5f, 1.f, 1.0f, 0.0f), //BACK Top Right     - [6]
		Vertex(0.5f,  -0.5f, 1.f, 1.0f, 1.0f), //BACK Bottom Right   - [7]

		Vertex(-0.5f,  -0.5f, -1.f, 0.0f, 1.0f), //FRONT Bottom Left   - [8]
		Vertex(-0.5f,   0.5f, -1.f, 0.0f, 0.0f), //FRONT Top Left      - [9]
		Vertex(-0.5f,   0.5f, 1.f, 1.0f, 0.0f), //BACK Top Left     - [10]
		Vertex(-0.5f,  -0.5f, 1.f, 1.0f, 1.0f), //BACK Bottom Left   - [11]

		Vertex(0.5f,  -0.5f, -1.f, 0.0f, 1.0f), //FRONT Bottom Right   - [12]
		Vertex(0.5f,   0.5f, -1.f, 0.0f, 0.0f), //FRONT Top Right      - [13]
		Vertex(0.5f,   0.5f, 1.f, 1.0f, 0.0f), //BACK Top Right     - [14]
		Vertex(0.5f,  -0.5f, 1.f, 1.0f, 1.0f), //BACK Bottom Right   - [15]

		Vertex(-0.5f,  -0.5f, -1.f, 0.0f, 1.0f), //FRONT Bottom Left   - [16]
		Vertex(-0.5f,   -0.5f, 1.f, 0.0f, 0.0f), //BACK Bottom Left      - [17]
		Vertex(0.5f,   -0.5f, 1.f, 1.0f, 0.0f), //BACK Bottom Right     - [18]
		Vertex(0.5f,  -0.5f, -1.f, 1.0f, 1.0f), //FRONT Bottom Right   - [19]

		Vertex(-0.5f,  0.5f, 1.f, 0.0f, 1.0f), //BACK Top Left   - [20]
		Vertex(-0.5f,   0.5f, -1.f, 0.0f, 0.0f), //FRONT Top Left      - [21]
		Vertex(0.5f,   0.5f, -1.f, 1.0f, 0.0f), //FRONT Top Right     - [22]
		Vertex(0.5f,  0.5f, 1.f, 1.0f, 1.0f), //BACK Top Right   - [23]
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
	
	
	if (!this->InitializeHelper(pDevice, pDeviceContext, L"Data\\Textures\\seamless_pavement.jpg", v, indices, pos, rotation)) {
		return false;
	}

	XMFLOAT3 wheelPos[] = {
		XMFLOAT3(0.5, -0.5, -1),
		XMFLOAT3(0.5, -0.5, 1),
		XMFLOAT3(-0.5, -0.5, -1),
		XMFLOAT3(-0.5, -0.5, 1),
	};

	XMFLOAT3 wheelRotation(0, XM_PIDIV2, 0);

	for (int i = 0; i < 4; i++) {
		this->attachments.emplace_back(new Wheel);
		if (!this->attachments[i]->Initialize(pDevice, pDeviceContext, wheelPos[i], wheelRotation)) {
			return false;
		}
		this->attachments[i]->SetScale(0.5);
	}

	this->thirdPerspective.SetPosition(0.f, 2.f, -5.f);
	this->thirdPerspective.SetProjectionValues(60.0f, static_cast<float>(800) / static_cast<float>(600), 0.1f, 1000.0f);
	this->thirdPerspective.attachedOn = this;
	
	this->firstPerspective.SetPosition(0.f, 0.5f, 1.f);
	this->firstPerspective.SetProjectionValues(60.0f, static_cast<float>(800) / static_cast<float>(600), 0.1f, 1000.0f);
	this->firstPerspective.attachedOn = this;
	return true;
}

Car::~Car() {}

void Car::ApplyMovement() {
	Actor::ApplyMovement();
	//An ugly way to force camera call ApplyMovement to update matrices
	this->firstPerspective.ApplyMovement();
	this->thirdPerspective.ApplyMovement();
}

