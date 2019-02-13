#include "Actor.h"



void Actor::SetScale(float scale) {
	this->scaleMatrix = XMMatrixScaling(scale, scale, scale);
}

void Actor::AdjustScale(float scale) {
	this->scaleMatrix *= scale;
}

void Actor::SetTexture(ID3D11ShaderResourceView * texture) {
	this->texture = texture;
}

void Actor::Draw(const XMMATRIX & viewProjectionMatrix, const XMMATRIX& parentTransform) {
	//Update Constant buffer with WVP Matrix
	XMMATRIX transformMatrix = this->scaleMatrix * this->worldMatrix * parentTransform * viewProjectionMatrix;
	this->cb_vs_vertexshader.data.wpvMatrix = transformMatrix; //Calculate World-View-Projection Matrix
	this->cb_vs_vertexshader.data.wpvMatrix = XMMatrixTranspose(this->cb_vs_vertexshader.data.wpvMatrix);

	XMMATRIX worldTransform = this->scaleMatrix * this->worldMatrix * parentTransform;
	this->cb_vs_vertexshader.data.worldMatrix = worldTransform; //Calculate World-View-Projection Matrix
	this->cb_vs_vertexshader.data.worldMatrix = XMMatrixTranspose(this->cb_vs_vertexshader.data.worldMatrix);

	this->cb_vs_vertexshader.ApplyChanges();
	this->deviceContext->VSSetConstantBuffers(0, 1, this->cb_vs_vertexshader.GetAddressOf());

	this->deviceContext->PSSetShaderResources(0, 1, this->texture.GetAddressOf()); //Set Texture
	this->deviceContext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	UINT offset = 0;
	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(), &offset);
	this->deviceContext->DrawIndexed(this->indexBuffer.IndexCount(), 0, 0); //Draw

	for (auto& a : attachments) {
		a->Draw(viewProjectionMatrix, worldTransform);
	}
}

Actor::~Actor() {}

//======================
//	setup
//		texture
//		vertex buffer
//		index buffer
//	initialize
//		position
//		rotation
//======================
bool Actor::InitializeHelper(ID3D11Device * device, ID3D11DeviceContext * deviceContext, const std::wstring& texturePath, std::vector<Vertex>& v, std::vector<DWORD>& indices, const XMFLOAT3 & pos, const XMFLOAT3 & rotation) {
	this->device = device;
	this->deviceContext = deviceContext;
	this->texture = texture;
	
	try {
		auto hr = this->cb_vs_vertexshader.Initialize(this->device, this->deviceContext);
		COM_ERROR_IF_FAILED(hr, "Failed to initialize constant buffer.");

		hr = DirectX::CreateWICTextureFromFile(this->device, texturePath.c_str(), nullptr, texture.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "Failed to create wic texture from file.");

		//Load Vertex Data
		hr = this->vertexBuffer.Initialize(this->device, v.data(), v.size());
		COM_ERROR_IF_FAILED(hr, "Failed to initialize vertex buffer.");
		
		hr = this->indexBuffer.Initialize(this->device, indices.data(), indices.size());
		COM_ERROR_IF_FAILED(hr, "Failed to initialize index buffer.");
	}
	catch (COMException & exception) {
		ErrorLogger::Log(exception);
		return false;
	}

	this->SetPosition(pos);
	this->SetRotation(rotation);
	this->ApplyMovement();
	return true;
}
