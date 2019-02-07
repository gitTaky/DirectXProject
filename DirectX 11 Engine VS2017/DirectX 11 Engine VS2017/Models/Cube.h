#pragma once
#include "../GameObjects/Actor.h"
class Cube :
	public Actor {
public:
	Cube();
	virtual bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation = { 0.f, 0.f, 0.f }) override;
	virtual void Tick(double delta) override;
	virtual ~Cube();
};

