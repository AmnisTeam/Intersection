#include "pch.h"
#include "Mesh.h"
#include "RenderWindow.h"

Mesh::Mesh(RenderWindow* renderWindow, std::vector<Vertex> vertices, std::vector<int> indices, VertexShader* vertexShader, PixelShader* pixelShader)
{
	this->vertices = vertices;
	this->indices = indices;
	this->renderWindow = renderWindow;
	constantBuffersSystem = new ConstantBuffersSystem(renderWindow);
	setupMesh(renderWindow, vertexShader, pixelShader);
}

void Mesh::setupMesh(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader)
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
	vertexBuffer = new Buffer(renderWindow->graphics, D3D11_BIND_VERTEX_BUFFER, vertices.data(), vertices.size() * sizeof(Vertex));

	constantBuffersSystem->VSAddValue(0, &modelMatrix, "ModelMatrix", sizeof(modelMatrix));
	constantBuffersSystem->VSAddValue(0, &MVP, "MVP", sizeof(MVP));
	constantBuffersSystem->VSAddValue(0, nullptr, "CameraPositoin", sizeof(float4));
	constantBuffersSystem->VSInit(0);

	indexBuffer = new Buffer(renderWindow->graphics, D3D11_BIND_INDEX_BUFFER, indices.data(), indices.size() * sizeof(int));
	sampleState = new SampleState(renderWindow->graphics);
	this->vertexShader = vertexShader;
	this->pixelShader = pixelShader;
}

void Mesh::setTexture(Texture* texture, int slot)
{
	textures[slot] = texture;
}

void Mesh::update(RenderTarget* renderTarget, RenderState state)
{
	Camera* camera = state.renderWindow->boundCamera;
	Graphics* graphics = state.renderWindow->graphics;
	DirectX::XMMATRIX modelMatrix = state.modelMatrix;
	DirectX::XMMATRIX preTransopesedMVP = DirectX::XMMatrixIdentity();
	preTransopesedMVP *= modelMatrix;
	if (state.viewMatrixOn == true)
		preTransopesedMVP *= camera->viewMatrix;
	if(state.projectionMatrixOn == true)
		preTransopesedMVP *= camera->projectionMatrix;

	MVP = DirectX::XMMatrixTranspose(preTransopesedMVP);
	modelMatrix = DirectX::XMMatrixTranspose(modelMatrix);

	constantBuffersSystem->VSUpdateValue(0, "ModelMatrix", &modelMatrix);
	constantBuffersSystem->VSUpdateValue(0, "MVP", &MVP);
	constantBuffersSystem->VSUpdateValue(0, "CameraPositoin", &camera->position);
}

void Mesh::draw(RenderTarget* renderTarget, RenderState state)
{
	update(renderTarget, state);

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

	constantBuffersSystem->updateAndSetAll();

	state.renderWindow->graphics->deviceCon->IASetIndexBuffer(indexBuffer->get(), DXGI_FORMAT_R32_UINT, 0);
	vertexShader->setLayout(state.renderWindow->graphics);
	state.renderWindow->graphics->deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	state.renderWindow->graphics->deviceCon->DrawIndexed(indices.size(), 0, 0);
}