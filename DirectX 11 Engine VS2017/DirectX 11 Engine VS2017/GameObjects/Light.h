#pragma once
#include "MovableObject.h"
#include "../Graphics/ConstantBuffer.h"

class Light :
	public MovableObject {
public:
	Light();

	virtual bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation = { 0.f, 0.f, 0.f });
	virtual void ApplyMovement() override;
	ID3D11Buffer* const* GetLightBuffer() const;
	~Light();

//private:
	ConstantBuffer<CB_PS_dynamicLight> cb_ps_light;
};

