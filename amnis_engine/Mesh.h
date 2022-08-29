#pragma once
#include <vector>
#include "mymath.h"
#include "Graphics.h"
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

class Mesh : public Transformable
{
public:

	std::vector<Vertex> vertices;
	std::vector<int> indices;
	std::map<int, Texture*> textures;
	float someAngle;
	bool drawDepthStencil = false;
	DECL Mesh(Graphics* graphics, std::vector<Vertex> vertices, std::vector<int> indices, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void setTexture(Texture* texture, int slot);

	DECL void VSConstBufSet(ConstantBuffer* constantBuffer, unsigned int const slot);
	DECL void PSConstBufSet(ConstantBuffer* constantBuffer, unsigned int const slot);
	DECL void VSConstBufAdd(unsigned int const slot);
	DECL void PSConstBufAdd(unsigned int const slot);
	DECL void VSConstBufAddValue(unsigned int slot, void* value, const char* key, unsigned int const size);
	DECL void PSConstBufAddValue(unsigned int slot, void* value, const char* key, unsigned int const size);
	DECL void VSConstBufUpdateValue(unsigned int const slot, const char* key, void* data);
	DECL void PSConstBufUpdateValue(unsigned int const slot, const char* key, void* data);
	DECL void VSConstBufInit(unsigned int const slot);
	DECL void PSConstBufInit(unsigned int const slot);

	DECL void draw(RenderTarget* renderTarget, RenderState renderState);
private:
	Graphics* graphics;
	Buffer* vertexBuffer;
	std::map<unsigned int, ConstantBuffer*> constantBuffersVS;
	std::map<unsigned int, ConstantBuffer*> constantBuffersPS;
	Buffer* indexBuffer;
	DefaultVertexShader* defaultVertexShader;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	ID3D11ShaderResourceView* SRVMink;
	SampleState* sampleState;
	DirectX::XMMATRIX MVP;
	ID3D11ShaderResourceView* SRVnormalMap;
	DECL void setupMesh(Graphics* graphics, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void update(RenderTarget* renderTarget, RenderState state);
};

