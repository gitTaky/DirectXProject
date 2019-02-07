#include "MovableObject.h"

MovableObject::MovableObject() : attachedOn(nullptr), pos(XMFLOAT3(0, 0, 0)), rot(XMFLOAT3(0, 0, 0)) {
	this->ApplyMovement();
}

const XMVECTOR & MovableObject::GetPositionVector() const {
	return this->posVector;
}

const XMFLOAT3 & MovableObject::GetPositionFloat3() const {
	return this->pos;
}

const XMVECTOR & MovableObject::GetRotationVector() const {
	return this->rotVector;
}

const XMFLOAT3 & MovableObject::GetRotationFloat3() const {
	return this->rot;
}

XMMATRIX MovableObject::GetAbsoluteTransform() const {
	if (this->attachedOn != nullptr) {
		return  this->worldMatrix * this->attachedOn->GetAbsoluteTransform();
	}
	else {
		return this->worldMatrix;
	}
}

XMMATRIX MovableObject::GetAbsoluteRotation() const {
	if (this->attachedOn != nullptr) {
		return XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z) * this->attachedOn->GetAbsoluteRotation();
	}
	else {
		return XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
	}
}

void MovableObject::SetPosition(const XMVECTOR & pos) {
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->ApplyMovement();
}

void MovableObject::SetPosition(const XMFLOAT3 & pos) {
	this->pos = pos;
	this->posVector = XMLoadFloat3(&this->pos);
	this->ApplyMovement();
}

void MovableObject::SetPosition(float x, float y, float z) {
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->ApplyMovement();
}

void MovableObject::AdjustPosition(const XMVECTOR & pos) {
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->ApplyMovement();
}

void MovableObject::AdjustPosition(const XMFLOAT3 & pos) {
	this->pos.x += pos.y;
	this->pos.y += pos.y;
	this->pos.z += pos.z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->ApplyMovement();
}

void MovableObject::AdjustPosition(float x, float y, float z) {
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->ApplyMovement();
}

void MovableObject::AdjustPosition(const XMMATRIX & transformMatrix) {
	this->posVector = XMVector3TransformCoord(this->posVector, transformMatrix);
	XMStoreFloat3(&this->pos, this->posVector);
	this->ApplyMovement();
}

void MovableObject::SetRotation(const XMVECTOR & rot) {
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->ApplyMovement();
}

void MovableObject::SetRotation(const XMFLOAT3 & rot) {
	this->rot = rot;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->ApplyMovement();
}

void MovableObject::SetRotation(float x, float y, float z) {
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->ApplyMovement();
}

void MovableObject::AdjustRotation(const XMVECTOR & rot) {
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->ApplyMovement();
}

void MovableObject::AdjustRotation(const XMFLOAT3 & rot) {
	this->rot.x += rot.x;
	this->rot.y += rot.y;
	this->rot.z += rot.z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->ApplyMovement();
}

void MovableObject::AdjustRotation(float x, float y, float z) {
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->ApplyMovement();
}

void MovableObject::AdjustRotation(const XMMATRIX & transformMatrix) {
	this->rotVector = XMVector3TransformCoord(this->rotVector, transformMatrix);
	XMStoreFloat3(&this->rot, this->rotVector);
	this->ApplyMovement();
}

const XMVECTOR & MovableObject::GetForwardVector(bool omitY) {
	return omitY ? this->vec_forward_noY : this->vec_forward;
}

const XMVECTOR & MovableObject::GetRightVector(bool omitY) {
	return omitY ? this->vec_right_noY : this->vec_right;
}

const XMVECTOR & MovableObject::GetBackwardVector(bool omitY) {
	return omitY ? this->vec_backward_noY : this->vec_backward;
}

const XMVECTOR & MovableObject::GetLeftVector(bool omitY) {
	return omitY ? this->vec_left_noY : this->vec_left;
}

void MovableObject::MoveForward(double delta) {
	this->AdjustPosition(this->vec_forward * this->speed * delta);
}

void MovableObject::MoveBackward(double delta) {
	this->AdjustPosition(this->vec_backward * this->speed * delta);
}

void MovableObject::MoveLeft(double delta) {
	this->AdjustPosition(this->vec_left * this->speed * delta);
}

void MovableObject::MoveRight(double delta) {
	this->AdjustPosition(this->vec_right * this->speed * delta);
}

void MovableObject::MoveUp(double delta) {
	this->AdjustPosition(this->vec_up * this->speed * delta);
}

void MovableObject::MoveDown(double delta) {
	this->AdjustPosition(this->vec_down * this->speed * delta);
}

void MovableObject::RotateLeft(double delta) {
	this->AdjustRotation(this->DEFAULT_DOWN_VECTOR * this->speed * delta);
}

void MovableObject::RotateRight(double delta) {
	this->AdjustRotation(this->DEFAULT_UP_VECTOR * this->speed * delta);
}

void MovableObject::RotateUp(double delta) {
	this->AdjustRotation(this->DEFAULT_RIGHT_VECTOR * this->speed * delta);
}

void MovableObject::RotateDown(double delta) {
	this->AdjustRotation(-this->DEFAULT_LEFT_VECTOR * this->speed * delta);
}

void MovableObject::RollLeft(double delta) {
	//this->AdjustPosition(this->vec_backward * this->speed * delta);
}

void MovableObject::RollRight(double delta) {
	//this->AdjustPosition(this->vec_backward * this->speed * delta);
}

void MovableObject::Tick(double delta) {}


void MovableObject::ApplyMovement() //Updates view matrix and also updates the movement vectors
{
	this->worldMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z) * XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	this->UpateDirectionVectors();
}

void MovableObject::UpateDirectionVectors() {
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, 0.0f);
	this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
	this->vec_up = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, vecRotationMatrix);
	this->vec_down = XMVector3TransformCoord(this->DEFAULT_DOWN_VECTOR, vecRotationMatrix);

	vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vec_forward_noY = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->vec_backward_noY = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	this->vec_left_noY = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	this->vec_right_noY = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
	this->vec_up_noY = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, vecRotationMatrix);
	this->vec_down_noY = XMVector3TransformCoord(this->DEFAULT_DOWN_VECTOR, vecRotationMatrix);
}

MovableObject::~MovableObject() {}
