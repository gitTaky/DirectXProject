#include "Camera.h"

Camera::Camera()
{
	this->pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->posVector = XMLoadFloat3(&this->pos);
	this->rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->rotVector = XMLoadFloat3(&this->rot);
	//this->UpdateViewMatrix();
	this->ApplyMovement();
}

void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	float fovRadians = (fovDegrees / 360.0f) * XM_2PI;
	this->projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

const XMMATRIX & Camera::GetViewMatrix() const
{
	return this->viewMatrix;
}

const XMMATRIX & Camera::GetCenteredViewMatrix() const {
	return this->centeredviewMatrix;
}

const XMMATRIX & Camera::GetProjectionMatrix() const
{
	return this->projectionMatrix;
}

void Camera::SetLookAtPos(XMFLOAT3 lookAtPos)
{
	//Verify that look at pos is not the same as cam pos. They cannot be the same as that wouldn't make sense and would result in undefined behavior.
	if (lookAtPos.x == this->pos.x && lookAtPos.y == this->pos.y && lookAtPos.z == this->pos.z)
		return;

	lookAtPos.x = this->pos.x - lookAtPos.x;
	lookAtPos.y = this->pos.y - lookAtPos.y;
	lookAtPos.z = this->pos.z - lookAtPos.z;

	float pitch = 0.0f;
	if (lookAtPos.y != 0.0f)
	{
		const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
		pitch = atan(lookAtPos.y / distance);
	}

	float yaw = 0.0f;
	if (lookAtPos.x != 0.0f)
	{
		yaw = atan(lookAtPos.x / lookAtPos.z);
	}
	if (lookAtPos.z > 0)
		yaw += XM_PI;

	this->SetRotation(pitch, yaw, 0.0f);
}

void Camera::ApplyMovement() {
	auto absoluteTransform = this->GetAbsoluteTransform();
	auto absoluteRotation = this->GetAbsoluteRotation();

	//Calculate camera rotation matrix

	//Calculate up direction based on current rotation
	XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, absoluteRotation);
	//Calculate unit vector of cam target based off camera forward value transformed by cam rotation matrix
	XMVECTOR camTarget = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, absoluteRotation);

	//Rebuild view matrix
	this->centeredviewMatrix = XMMatrixLookAtLH({ 0.f, 0.f, 0.f, 0.f }, camTarget, upDir);

	//Adjust cam target to be offset by the camera's current position
	auto camPos = XMVector3TransformCoord(this->posVector, absoluteTransform);
	camTarget += camPos;
	//Rebuild view matrix
	this->viewMatrix = XMMatrixLookAtLH(camPos, camTarget, upDir);

	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
}