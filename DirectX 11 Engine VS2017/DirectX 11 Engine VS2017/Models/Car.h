#pragma once
#include "../GameObjects/Actor.h"
#include "Wheel.h"
#include "../GameObjects/Camera.h"

class Car :
	public Actor {
public:
	Car();

	virtual bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation = {0.f, 0.f, 0.f}) override;

	virtual ~Car();

	Camera firstPerspective;
	Camera thirdPerspective;
protected:
	virtual void ApplyMovement() override;
};

