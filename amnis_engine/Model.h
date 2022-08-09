#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "Camera.h"
#include <vector>
#include "Transformable.h"

class Model : public Transformable
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
	DECL Model(Graphics* graphics, char* modelPath);
	DECL Model(Graphics* graphics, char* modelPath, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void setTexture(Texture* texture, unsigned int slot);
	DECL void deleteTexture(unsigned int slot);
	DECL std::vector<Texture*> loadMaterialTextures(Graphics* graphics, aiMaterial* mat, aiTextureType type);
	DECL virtual void draw(Graphics* graphics, Camera* camera);
	DECL virtual void draw(Graphics* graphics, Camera* camera, DirectX::XMMATRIX modelMatrix);
	DECL void draw(RenderTarget* renderTarget, RenderState renderState);
	//void draw(Graphics* graphics, Camera* camera, Transform* transform);
private:
	std::vector<Mesh> meshes;
	std::string directory;
	DECL void loadModel(Graphics* graphics, std::string path, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void processNode(Graphics* graphics, aiNode* node, const aiScene* scene, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL Mesh processMesh(Graphics* graphics, const aiScene* scene, aiMesh* mesh, VertexShader* vertexShader, PixelShader* pixelShader);
};

