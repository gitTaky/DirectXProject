#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class MovableObject {
public:
	MovableObject();

	virtual const XMVECTOR & GetPositionVector() const;
	virtual const XMFLOAT3 & GetPositionFloat3() const;
	virtual const XMVECTOR & GetRotationVector() const;
	virtual const XMFLOAT3 & GetRotationFloat3() const;

	virtual XMMATRIX GetAbsoluteTransform() const;
	virtual XMMATRIX GetAbsoluteRotation() const;

	virtual void SetPosition(const XMVECTOR & pos);
	virtual void SetPosition(const XMFLOAT3 & pos);
	virtual void SetPosition(float x, float y, float z);
	virtual void AdjustPosition(const XMVECTOR & pos);
	virtual void AdjustPosition(const XMFLOAT3 & pos);
	virtual void AdjustPosition(float x, float y, float z);
	virtual void AdjustPosition(const XMMATRIX & transformMatrix);

	virtual void SetRotation(const XMVECTOR & rot);
	virtual void SetRotation(const XMFLOAT3 & rot);
	virtual void SetRotation(float x, float y, float z);
	virtual void AdjustRotation(const XMVECTOR & rot);
	virtual void AdjustRotation(const XMFLOAT3 & rot);
	virtual void AdjustRotation(float x, float y, float z);
	virtual void AdjustRotation(const XMMATRIX & transformMatrix);

	virtual const XMVECTOR & GetForwardVector();
	virtual const XMVECTOR & GetRightVector();
	virtual const XMVECTOR & GetBackwardVector();
	virtual const XMVECTOR & GetLeftVector();

	virtual void MoveForward(double delta);
	virtual void MoveBackward(double delta);
	virtual void MoveLeft(double delta);
	virtual void MoveRight(double delta);
	virtual void MoveUp(double delta);
	virtual void MoveDown(double delta);

	virtual void RotateLeft(double delta);
	virtual void RotateRight(double delta);
	virtual void RotateUp(double delta);
	virtual void RotateDown(double delta);
	virtual void RollLeft(double delta);
	virtual void RollRight(double delta);

	virtual void ApplyMovement();

	virtual void Tick(double delta);

	virtual ~MovableObject();

	MovableObject* attachedOn;
protected:
	XMMATRIX worldMatrix = XMMatrixIdentity();
	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMFLOAT3 pos;
	XMFLOAT3 rot;

	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_DOWN_VECTOR = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_BACKWARD_VECTOR = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR vec_forward;
	XMVECTOR vec_left;
	XMVECTOR vec_right;
	XMVECTOR vec_backward;
	XMVECTOR vec_up;
	XMVECTOR vec_down;

	float speed = 0.01f;
};

