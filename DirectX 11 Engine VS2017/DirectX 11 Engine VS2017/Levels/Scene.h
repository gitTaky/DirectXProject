#pragma once
#include "../Models/Car.h"
#include "../Models/Floor.h"
#include "../Models/SkyBox.h"
#include "../Models/Cube.h"
#include "../GameObjects/Camera.h"
#include "../GameObjects/Light.h"
#include <unordered_map>
#include <memory>


class Scene {
public:
	Scene();

	bool Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, int windowWidth, int windowHeight);
	void Draw(const Camera* appliedCamera);
	void Tick(double delta);
	~Scene();

	std::unordered_map<std::string, std::unique_ptr<Actor> > actors;
	SkyBox skyBox;
	Camera camera;
	Light light;
private:
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDeviceContext;

	ConstantBuffer<CB_PS_ambientLight> cb_ps_light;
};

