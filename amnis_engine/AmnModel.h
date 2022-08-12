#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "Camera.h"
#include <vector>
#include "Transformable.h"

class AmnModel : public Transformable
{
public:
	struct TextureStruct
	{
		Texture* texture;
		unsigned int slot;
	};
	std::map<unsigned int, Texture*> textures;
	std::string extension;
	bool drawDepthStencil = true;
	DECL AmnModel(Graphics* const graphics, std::vector<Vertex> const vertices, std::vector<int> const indices, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL AmnModel(Graphics* graphics, char* modelPath);
	DECL AmnModel(Graphics* graphics, char* modelPath, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void setTexture(Texture* texture, unsigned int slot);
	DECL void deleteTexture(unsigned int slot);
	DECL std::vector<Texture*> loadMaterialTextures(Graphics* graphics, aiMaterial* mat, aiTextureType type);
	DECL void draw(RenderTarget* renderTarget, RenderState renderState);

	DECL void VSConstBufSet(ConstantBuffer* constantBuffer, unsigned int const slot);
	DECL void PSConstBufSet(ConstantBuffer* constantBuffer, unsigned int const slot);
	DECL void VSConstBufAdd(unsigned int const slot);
	DECL void PSConstBufAdd(unsigned int const slot);
	DECL void VSConstBufAddValue(unsigned int slot, void* value, const char* key, unsigned int const size);
	DECL void PSConstBufAddValue(unsigned int slot, void* value, const char* key, unsigned int const size);
	DECL void VSConstBufUpdateValue(unsigned int const slot, unsigned int dataID, void* data);
	DECL void PSConstBufUpdateValue(unsigned int const slot, unsigned int dataID, void* data);
	DECL void VSConstBufInit(unsigned int const slot);
	DECL void PSConstBufInit(unsigned int const slot);

private:
	Graphics* graphics;
	std::vector<Mesh> meshes;
	std::string directory;
	std::map<unsigned int, ConstantBuffer*> constantBuffersVS;
	std::map<unsigned int, ConstantBuffer*> constantBuffersPS;
	DECL void loadModel(Graphics* graphics, std::string path, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void loadModel(Graphics* graphics, void* model, const unsigned int modelSize, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void processNode(Graphics* graphics, aiNode* node, const aiScene* scene, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL Mesh processMesh(Graphics* graphics, const aiScene* scene, aiMesh* mesh, VertexShader* vertexShader, PixelShader* pixelShader);
};

