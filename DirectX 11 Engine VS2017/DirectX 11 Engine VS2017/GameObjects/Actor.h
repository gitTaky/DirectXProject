#pragma once
#include "../Graphics/Vertex.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/ConstantBuffer.h"
#include "MovableObject.h"
#include <vector>
#include <memory>
#include <WICTextureLoader.h>

class Actor :
	public MovableObject {
public:
	Actor() {}

	virtual bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, const XMFLOAT3& pos, const XMFLOAT3& rotation = {0.f, 0.f, 0.f}) = 0;

	virtual void SetScale(float scale);
	virtual void AdjustScale(float scale);

	virtual void SetTexture(ID3D11ShaderResourceView * texture);
	virtual void Draw(const XMMATRIX & viewProjectionMatrix, const XMMATRIX& parentTransform = XMMatrixIdentity());

	virtual ~Actor();

	std::vector<std::unique_ptr<Actor>> attachments;
protected:
	virtual bool InitializeHelper(ID3D11Device * device, ID3D11DeviceContext * deviceContext, const std::wstring& texturePath, std::vector<Vertex>& v, std::vector<DWORD>& indices, const XMFLOAT3& pos, const XMFLOAT3& rotation);
	ID3D11Device * device = nullptr;
	ID3D11DeviceContext * deviceContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	XMMATRIX scaleMatrix = XMMatrixScaling(1, 1, 1);
	
	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;

	ConstantBuffer<CB_VS_vertexshader> cb_vs_vertexshader;
};

