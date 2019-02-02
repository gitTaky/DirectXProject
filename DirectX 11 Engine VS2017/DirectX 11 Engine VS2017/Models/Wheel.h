#pragma once
#include "../GameObjects/Actor.h"
class Wheel :
	public Actor {
public:
	Wheel();

	virtual bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation = { 0.f, 0.f, 0.f }) override;
	//virtual bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView * texture, const XMFLOAT3& pos) override;
	//virtual bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView * texture, const XMVECTOR& pos) override;


	virtual ~Wheel();
};

