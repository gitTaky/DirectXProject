#include "Scene.h"

#include "../Graphics/ImGui/imgui.h"
#include "../Graphics/ImGui/imgui_impl_win32.h"
#include "../Graphics/ImGUI/imgui_impl_dx11.h"

Scene::Scene() {}

bool Scene::Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, int windowWidth, int windowHeight) {
	this->pDevice = pDevice;
	this->pDeviceContext = pDeviceContext;

	try {
		actors["car"] = std::make_unique<Car>();
		actors["floor"] = std::make_unique<Floor>();
		actors["cube"] = std::make_unique<Cube>();

		if (!this->actors["car"]->Initialize(this->pDevice, this->pDeviceContext, DirectX::XMFLOAT3(0, 0, 0)))
			return false;

		if (!this->actors["floor"]->Initialize(this->pDevice, this->pDeviceContext, DirectX::XMFLOAT3(0, -1, 0)))
			return false;

		this->actors["floor"]->SetScale(200);

		if (!this->actors["cube"]->Initialize(this->pDevice, this->pDeviceContext, DirectX::XMFLOAT3(1, 0, 0)))
			return false;

		if (!this->skyBox.Initialize(this->pDevice, this->pDeviceContext, DirectX::XMFLOAT3(0, -1, 0)))
			return false;

		this->skyBox.SetScale(200);

		if (!this->light.Initialize(this->pDevice, this->pDeviceContext, DirectX::XMFLOAT3(0, 0, 0))) {
			return false;
		}

		camera.SetPosition(0.0f, 0.0f, -2.0f);
		camera.SetProjectionValues(60.0f, static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 1000.0f);

		auto hr = this->cb_ps_light.Initialize(this->pDevice, this->pDeviceContext);
		COM_ERROR_IF_FAILED(hr, "Failed to create constant buffer.");

		this->cb_ps_light.data.ambientLightColor = XMFLOAT3(1.f, 1.f, 1.f);
		this->cb_ps_light.data.ambientLightStrength = 1.f;
	}
	catch (COMException & exception) {
		ErrorLogger::Log(exception);
		return false;
	}
	return true;
}

void Scene::Draw(const Camera* appliedCamera) {
	//Lights
	this->light.cb_ps_light.ApplyChanges();
	this->pDeviceContext->PSSetConstantBuffers(1, 1, this->light.GetLightBuffer());

	this->cb_ps_light.ApplyChanges();
	this->pDeviceContext->PSSetConstantBuffers(0, 1, this->cb_ps_light.GetAddressOf());
	
	//Actors
	auto vpMatrix = appliedCamera->GetViewMatrix() * appliedCamera->GetProjectionMatrix();
	for (const auto& p : actors) {
		p.second->Draw(vpMatrix);
	}

	//SkyBox
	auto cvpMatrix = appliedCamera->GetCenteredViewMatrix() * appliedCamera->GetProjectionMatrix();
	skyBox.Draw(cvpMatrix);

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//Create ImGui Test Window
	ImGui::Begin("Light Constrols");
	ImGui::DragFloat3("Ambient Light Color", &this->cb_ps_light.data.ambientLightColor.x, 0.01f, 0.f, 1.f);
	ImGui::DragFloat("Ambient Light Strength", &this->cb_ps_light.data.ambientLightStrength, 0.01f, 0.f, 1.f);
	ImGui::DragFloat3("Dynamic Light Color", &this->light.cb_ps_light.data.dynamicLightColor.x, 0.01f, 0.f, 1.f);
	ImGui::DragFloat("Dynamic Light Strength", &this->light.cb_ps_light.data.dynamicLightStrength, 0.01f, 0.f, 10.f);
	ImGui::DragFloat3("Dynamic Light Position", &this->light.cb_ps_light.data.dynamicLightPosition.x, 0.01f, 0.f, 1.f);
	ImGui::End();
	//Assemble Together Draw Data
	ImGui::Render();
	//Render Draw Data
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void Scene::Tick(double delta) {
	for (auto& p : actors) {
		p.second->Tick(delta);
	}
}

Scene::~Scene() {}
