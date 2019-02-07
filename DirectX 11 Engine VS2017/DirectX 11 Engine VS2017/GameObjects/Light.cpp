#include "Light.h"



Light::Light() {}


bool Light::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation) {
	try {
		auto hr = this->cb_ps_light.Initialize(device, deviceContext);
		COM_ERROR_IF_FAILED(hr, "Failed to initialize constant buffer.");
	}
	catch (COMException & exception) {
		ErrorLogger::Log(exception);
		return false;
	}

	this->cb_ps_light.data.dynamicLightColor = DirectX::XMFLOAT3(1.f, 1.f, 1.f);
	this->cb_ps_light.data.dynamicLightStrength = 1.f;
	this->SetPosition(pos);
	return true;
}

void Light::ApplyMovement() {
	MovableObject::ApplyMovement();
	this->cb_ps_light.data.dynamicLightPosition = this->pos;
	this->cb_ps_light.ApplyChanges();
}

ID3D11Buffer * const * Light::GetLightBuffer() const {
	return this->cb_ps_light.GetAddressOf();
}

Light::~Light() {}
