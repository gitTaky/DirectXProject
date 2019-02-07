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

	virtual void Accelerate(double dt);
	virtual void TurnRight(double rate);
protected:
	virtual void ApplyMovement() override;

	XMVECTOR TURNING_RATE = XMVectorSet(0.f, XM_PIDIV4 / 10, 0.f, 0.f);
	float turningRight = 0;
};

