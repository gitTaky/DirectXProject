#pragma once
#include <DirectXMath.h>
#include "MovableObject.h"
using namespace DirectX;

class Camera : public MovableObject
{
public:
	Camera();
	void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);

	const XMMATRIX & GetViewMatrix() const;
	const XMMATRIX & GetCenteredViewMatrix() const;
	const XMMATRIX & GetProjectionMatrix() const;

	void SetLookAtPos(XMFLOAT3 lookAtPos);

	virtual void ApplyMovement() override;
private:

	XMMATRIX viewMatrix;
	XMMATRIX centeredviewMatrix;
	XMMATRIX projectionMatrix;
};
