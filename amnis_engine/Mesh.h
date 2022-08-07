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

class Mesh : public Transformable
{
public:

	std::vector<Vertex> vertices;
	std::vector<int> indices;
	std::map<int, Texture*> textures;
	float someAngle;
	bool drawDepthStencil = false;
	Mesh(Graphics* graphics, std::vector<Vertex> vertices, std::vector<int> indices, VertexShader* vertexShader, PixelShader* pixelShader);
	void setTexture(Texture* texture, int slot);
	void draw(Graphics* graphics, Camera* camera);
	void draw(Graphics* graphics, Camera* camera, DirectX::XMMATRIX modelMatrix);
	void draw(RenderTarget* renderTarget, RenderState renderState);
	//void draw(Graphics* graphics, Camera* camera, Transform* transform);
private:
	Buffer* vertexBuffer;
	Buffer* constantBuffer;
	Buffer* indexBuffer;
	DefaultVertexShader* defaultVertexShader;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	ID3D11ShaderResourceView* SRVMink;
	SampleState* sampleState;
	DirectX::XMMATRIX MVP;
	ID3D11ShaderResourceView* SRVnormalMap;
	void setupMesh(Graphics* graphics, VertexShader* vertexShader, PixelShader* pixelShader);
	void update(Graphics* graphics, Camera* camera);
	void update(Graphics* graphics, Camera* camera, DirectX::XMMATRIX modelMatrix);
	//void update(Graphics* graphics, Camera* camera, Transform* transform);
};

