#include "pch.h"
#include "Mesh.h"
#include "RenderWindow.h"

Mesh::Mesh(Graphics* graphics, std::vector<Vertex> vertices, std::vector<int> indices, VertexShader* vertexShader, PixelShader* pixelShader)
{
	this->vertices = vertices;
	this->indices = indices;
	setupMesh(graphics, vertexShader, pixelShader);
}

void Mesh::setupMesh(Graphics* graphics, VertexShader* vertexShader, PixelShader* pixelShader)
{
	for (int i = 0; i < indices.size(); i += 3)
	{
		int vertex1 = indices[i];
		int vertex2 = indices[i + 1];
		int vertex3 = indices[i + 2];

		float dU1 = vertices[vertex2].texCoord.x - vertices[vertex1].texCoord.x;
		float dU2 = vertices[vertex3].texCoord.x - vertices[vertex2].texCoord.x;

		float dV1 = vertices[vertex2].texCoord.y - vertices[vertex1].texCoord.y;
		float dV2 = vertices[vertex3].texCoord.y - vertices[vertex2].texCoord.y;

		if ((dU1 * dV2 - dU2 * dV1) == 0)
			int p = 5;

		float d = 1.0f / (dU1 * dV2 - dU2 * dV1);

		float3 E1 = {
			vertices[vertex2].pos.x - vertices[vertex1].pos.x,
			vertices[vertex2].pos.y - vertices[vertex1].pos.y,
			vertices[vertex2].pos.z - vertices[vertex1].pos.z,
		};

		float3 E2 = {
			vertices[vertex3].pos.x - vertices[vertex2].pos.x,
			vertices[vertex3].pos.y - vertices[vertex2].pos.y,
			vertices[vertex3].pos.z - vertices[vertex2].pos.z,
		};

		float3 B = {
			d * (dV2 * E1.x - dV1 * E2.x),
			d * (dV2 * E1.y - dV1 * E2.y),
			d * (dV2 * E1.z - dV1 * E2.z),
		};

		float3 T = {
			d * (dU1 * E2.x - dU2 * E1.x),
			d * (dU1 * E2.y - dU2 * E1.y),
			d * (dU1 * E2.z - dU2 * E1.z),
		};

		vertices[vertex1].tangent = T;
		vertices[vertex1].bitangent = B;

		vertices[vertex2].tangent = T;
		vertices[vertex2].bitangent = B;

		vertices[vertex3].tangent = T;
		vertices[vertex3].bitangent = B;
	}
	vertexBuffer = new Buffer(graphics, D3D11_BIND_VERTEX_BUFFER, vertices.data(), vertices.size() * sizeof(Vertex));
	constantBuffer = new Buffer(graphics, D3D11_BIND_CONSTANT_BUFFER, nullptr, sizeof(DirectX::XMMATRIX) * 2 + sizeof(float4), D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
	indexBuffer = new Buffer(graphics, D3D11_BIND_INDEX_BUFFER, indices.data(), indices.size() * sizeof(int));
	sampleState = new SampleState(graphics);
	this->vertexShader = vertexShader;
	this->pixelShader = pixelShader;
	//HRESULT hr = DirectX::CreateWICTextureFromFile(graphics->device, L"Wall_Stone_017_BaseColor.jpg", nullptr, &SRVMink);
	//if (FAILED(hr)) throw;
	//hr = DirectX::CreateWICTextureFromFile(graphics->device, L"Textures\\14015-normal.jpg", nullptr, &SRVnormalMap);
	//if (FAILED(hr)) throw;
}

void Mesh::setTexture(Texture* texture, int slot)
{
	textures[slot] = texture;
}

void Mesh::update(Graphics* graphics, Camera* camera)
{
	float3 position = getPosition();
	float3 rotation = getRotation();
	float3 scale = getScale();
	DirectX::XMMATRIX modelMatrix = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) * DirectX::XMMatrixRotationX(rotation.x) * DirectX::XMMatrixRotationY(rotation.y) * DirectX::XMMatrixRotationZ(rotation.z) * DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	MVP = DirectX::XMMatrixTranspose(modelMatrix * camera->viewMatrix * camera->projectionMatrix);
	modelMatrix = DirectX::XMMatrixTranspose(modelMatrix);

	D3D11_MAPPED_SUBRESOURCE ms{};
	graphics->deviceCon->Map(constantBuffer->get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	memcpy(ms.pData, &modelMatrix, sizeof(modelMatrix));
	char* lastPos = (char*)ms.pData + sizeof(modelMatrix);
	memcpy(lastPos, &MVP, sizeof(MVP));
	lastPos = lastPos + sizeof(MVP);
	memcpy(lastPos, &camera->position, sizeof(float4));
	graphics->deviceCon->Unmap(constantBuffer->get(), NULL);
}

void Mesh::update(Graphics* graphics, Camera* camera, DirectX::XMMATRIX modelMatrix)
{
	MVP = DirectX::XMMatrixTranspose(modelMatrix * camera->viewMatrix * camera->projectionMatrix);
	modelMatrix = DirectX::XMMatrixTranspose(modelMatrix);

	D3D11_MAPPED_SUBRESOURCE ms{};
	graphics->deviceCon->Map(constantBuffer->get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	memcpy(ms.pData, &modelMatrix, sizeof(modelMatrix));
	char* lastPos = (char*)ms.pData + sizeof(modelMatrix);
	memcpy(lastPos, &MVP, sizeof(MVP));
	lastPos = lastPos + sizeof(MVP);
	memcpy(lastPos, &camera->position, sizeof(float4));
	graphics->deviceCon->Unmap(constantBuffer->get(), NULL);
}

void Mesh::draw(Graphics* graphics, Camera* camera)
{
	update(graphics, camera);

	for (auto i = textures.begin(); i != textures.end(); i++)
		i->second->bind(i->first);

	//graphics->deviceCon->PSSetShaderResources(0, 1, &SRVMink);
	//graphics->deviceCon->PSSetShaderResources(1, 1, &SRVnormalMap);
	UINT strides = sizeof(Vertex);
	UINT offset = 0;
	if(drawDepthStencil)
		graphics->deviceCon->OMSetRenderTargets(1, &graphics->backRenderTarget, graphics->depthStencilView);
	else
		graphics->deviceCon->OMSetRenderTargets(1, &graphics->backRenderTarget, NULL);
	sampleState->set(graphics);
	graphics->deviceCon->IASetVertexBuffers(0, 1, vertexBuffer->getpp(), &strides, &offset);
	graphics->deviceCon->VSSetConstantBuffers(0, 1, constantBuffer->getpp());
	graphics->deviceCon->IASetIndexBuffer(indexBuffer->get(), DXGI_FORMAT_R32_UINT, 0);
	//vertexShader->setVertexShader(graphics);
	//graphics->deviceCon->PSSetShader(pixelShader->get(), NULL, NULL);
	vertexShader->setLayout(graphics);
	graphics->deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	graphics->deviceCon->DrawIndexed(indices.size(), 0, 0);
}

void Mesh::draw(Graphics* graphics, Camera* camera, DirectX::XMMATRIX modelMatrix)
{
	update(graphics, camera, modelMatrix);

	for (auto i = textures.begin(); i != textures.end(); i++)
		i->second->bind(i->first);

	//graphics->deviceCon->PSSetShaderResources(0, 1, &SRVMink);
	//graphics->deviceCon->PSSetShaderResources(1, 1, &SRVnormalMap);
	UINT strides = sizeof(Vertex);
	UINT offset = 0;
	if (drawDepthStencil)
		graphics->deviceCon->OMSetRenderTargets(1, &graphics->backRenderTarget, graphics->depthStencilView);
	else
		graphics->deviceCon->OMSetRenderTargets(1, &graphics->backRenderTarget, NULL);
	sampleState->set(graphics);
	graphics->deviceCon->IASetVertexBuffers(0, 1, vertexBuffer->getpp(), &strides, &offset);
	graphics->deviceCon->VSSetConstantBuffers(0, 1, constantBuffer->getpp());
	graphics->deviceCon->IASetIndexBuffer(indexBuffer->get(), DXGI_FORMAT_R32_UINT, 0);
	//vertexShader->setVertexShader(graphics);
	//graphics->deviceCon->PSSetShader(pixelShader->get(), NULL, NULL);
	vertexShader->setLayout(graphics);
	graphics->deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	graphics->deviceCon->DrawIndexed(indices.size(), 0, 0);
}

void Mesh::draw(RenderTarget* renderTarget, RenderState state)
{
	update(state.renderWindow->graphics, state.renderWindow->boundCamera, state.modelMatrix);

	for (auto i = textures.begin(); i != textures.end(); i++)
		i->second->bind(i->first);

	UINT strides = sizeof(Vertex);
	UINT offset = 0;
	if (state.depthStencilOn)
		state.renderWindow->graphics->deviceCon->OMSetRenderTargets(1, &renderTarget->renderTarget, state.renderWindow->graphics->depthStencilView);
	else
		state.renderWindow->graphics->deviceCon->OMSetRenderTargets(1, &renderTarget->renderTarget, NULL);
	sampleState->set(state.renderWindow->graphics);
	state.renderWindow->graphics->deviceCon->IASetVertexBuffers(0, 1, vertexBuffer->getpp(), &strides, &offset);
	state.renderWindow->graphics->deviceCon->VSSetConstantBuffers(0, 1, constantBuffer->getpp());
	state.renderWindow->graphics->deviceCon->IASetIndexBuffer(indexBuffer->get(), DXGI_FORMAT_R32_UINT, 0);
	//vertexShader->setVertexShader(graphics);
	//graphics->deviceCon->PSSetShader(pixelShader->get(), NULL, NULL);
	vertexShader->setLayout(state.renderWindow->graphics);
	state.renderWindow->graphics->deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	state.renderWindow->graphics->deviceCon->DrawIndexed(indices.size(), 0, 0);
}

//void Mesh::update(Graphics* graphics, Camera* camera, Transform* transform)
//{
//	transfrom.Update(position, rotation, scale);
//	transfrom.merge(transform);
//
//	MVP = DirectX::XMMatrixTranspose(transfrom.modelMatrix * camera->viewMatrix * camera->projectionMatrix);
//	DirectX::XMMATRIX modelMatrix = DirectX::XMMatrixTranspose(transfrom.modelMatrix);
//	D3D11_MAPPED_SUBRESOURCE ms{};
//	graphics->deviceCon->Map(constantBuffer->get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
//
//	memcpy(ms.pData, &modelMatrix, sizeof(modelMatrix));
//	char* lastPos = (char*)ms.pData + sizeof(modelMatrix);
//	memcpy(lastPos, &MVP, sizeof(MVP));
//	lastPos = lastPos + sizeof(MVP);
//	memcpy(lastPos, &camera->position, sizeof(float4));
//	graphics->deviceCon->Unmap(constantBuffer->get(), NULL);
//}
//
//void Mesh::draw(Graphics* graphics, Camera* camera, Transform* transform)
//{
//	update(graphics, camera, transform);
//
//	for (auto i = textures.begin(); i != textures.end(); i++)
//		i->second->bind(i->first);
//
//	//graphics->deviceCon->PSSetShaderResources(0, 1, &SRVMink);
//	//graphics->deviceCon->PSSetShaderResources(1, 1, &SRVnormalMap);
//	UINT strides = sizeof(Vertex);
//	UINT offset = 0;
//	if (drawDepthStencil)
//		graphics->deviceCon->OMSetRenderTargets(1, &graphics->backRenderTarget, graphics->depthStencilView);
//	else
//		graphics->deviceCon->OMSetRenderTargets(1, &graphics->backRenderTarget, NULL);
//	sampleState->set(graphics);
//	graphics->deviceCon->IASetVertexBuffers(0, 1, vertexBuffer->getpp(), &strides, &offset);
//	graphics->deviceCon->VSSetConstantBuffers(0, 1, constantBuffer->getpp());
//	graphics->deviceCon->IASetIndexBuffer(indexBuffer->get(), DXGI_FORMAT_R32_UINT, 0);
//	vertexShader->setVertexShader(graphics);
//	graphics->deviceCon->PSSetShader(pixelShader->get(), NULL, NULL);
//	vertexShader->setLayout(graphics);
//	graphics->deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	graphics->deviceCon->DrawIndexed(indices.size(), 0, 0);
//}
