#pragma once
#include <vector>
#include "mymath.h"
#include "MainWindow.h"
#include <DirectXMath.h>
#include "Buffer.h"
#include "VertexShader.h"
#include "pixelShader.h"
#include "DefaultVertexShader.h"
#include "SampleState.h"
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include "Camera.h"
#include <map>
#include "Texture.h"
#include "Transformable.h"
#include "ConstantBuffer.h"
#include <map>
#include "ConstantBuffersSystem.h"

class RenderWindow;

class Mesh : public Transformable
{
public:
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	std::map<int, Texture*> textures;
	float someAngle;
	bool drawDepthStencil = false;
	DECL Mesh(RenderWindow* renderWindow, std::vector<Vertex> vertices, std::vector<int> indices, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void setTexture(Texture* texture, int slot);
	DECL void draw(RenderTarget* renderTarget, RenderState renderState);
private:
	RenderWindow* renderWindow;
	Buffer* vertexBuffer;
	Buffer* indexBuffer;
	DefaultVertexShader* defaultVertexShader;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	ID3D11ShaderResourceView* SRVMink;
	SampleState* sampleState;
	DirectX::XMMATRIX MVP;
	ID3D11ShaderResourceView* SRVnormalMap;
	ConstantBuffersSystem* constantBuffersSystem;
	DECL void setupMesh(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void update(RenderTarget* renderTarget, RenderState state);
};

