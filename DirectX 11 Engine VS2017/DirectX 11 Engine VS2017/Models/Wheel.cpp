#include "Wheel.h"



Wheel::Wheel() {}


bool Wheel::Initialize(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation) {
	//Textured Square
	const float length = 1;
	const float widthDiv2 = 0.15;
	const int points = 16;
	std::vector<Vertex> v(points * 2 + 2);
	//FRONT
	for (int i = 0; i < points; i++) {
		v[i] = Vertex(length * sin(XM_2PI * (static_cast<float>(i) / static_cast<float>(points))),
			length * cos(XM_2PI * (static_cast<float>(i) / static_cast<float>(points))),
			-widthDiv2,
			0.5 * sin(XM_2PI * (static_cast<float>(i) / static_cast<float>(points))) + 0.5,
			0.5 * cos(XM_2PI * (static_cast<float>(i) / static_cast<float>(points))) + 0.5);
	}
	//BACK
	for (int i = 0; i < points; i++) {
		v[i + points] = Vertex(length * sin(XM_2PI * (static_cast<float>(i) / static_cast<float>(points))),
			length * cos(XM_2PI * (static_cast<float>(i) / static_cast<float>(points))),
			widthDiv2,
			0.5 * sin(XM_2PI * (static_cast<float>(i) / static_cast<float>(points))) + 0.5,
			0.5 * cos(XM_2PI * (static_cast<float>(i) / static_cast<float>(points))) + 0.5);
	}
	//FRONT CENTER
	v[2 * points] = Vertex(0.f,
		0.f,
		-widthDiv2,
		0.5f,
		0.5f);
	//BACK CENTER
	v[2 * points + 1] = Vertex(0.f,
		0.f,
		widthDiv2,
		0.5f,
		0.5f);

	std::vector<DWORD> indices(points * 4 * 3);
	for (int i = 0; i < points; i++) {
		indices[i * 4 * 3] = (i + 1) % points;
		indices[i * 4 * 3 + 1] = points * 2;
		indices[i * 4 * 3 + 2] = i;

		indices[i * 4 * 3 + 3] = i + points;
		indices[i * 4 * 3 + 4] = points * 2 + 1;
		indices[i * 4 * 3 + 5] = (i + 1) % points + points;

		indices[i * 4 * 3 + 6] = (i + 1) % points + points;
		indices[i * 4 * 3 + 7] = (i + 1) % points;
		indices[i * 4 * 3 + 8] = i;

		indices[i * 4 * 3 + 9] = i + points;
		indices[i * 4 * 3 + 10] = (i + 1) % points + points;
		indices[i * 4 * 3 + 11] = i;
	}
	
	return this->InitializeHelper(pDevice, pDeviceContext, L"Data\\Textures\\seamless_grass.jpg", v, indices, pos, rotation);
}


Wheel::~Wheel() {}
