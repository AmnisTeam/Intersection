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
	Model(Graphics* graphics, char* modelPath);
	Model(Graphics* graphics, char* modelPath, VertexShader* vertexShader, PixelShader* pixelShader);
	void setTexture(Texture* texture, unsigned int slot);
	void deleteTexture(unsigned int slot);
	std::vector<Texture*> loadMaterialTextures(Graphics* graphics, aiMaterial* mat, aiTextureType type);
	virtual void draw(Graphics* graphics, Camera* camera);
	virtual void draw(Graphics* graphics, Camera* camera, DirectX::XMMATRIX modelMatrix);
	void draw(RenderTarget* renderTarget, RenderState renderState);
	//void draw(Graphics* graphics, Camera* camera, Transform* transform);
private:
	std::vector<Mesh> meshes;
	std::string directory;
	void loadModel(Graphics* graphics, std::string path, VertexShader* vertexShader, PixelShader* pixelShader);
	void processNode(Graphics* graphics, aiNode* node, const aiScene* scene, VertexShader* vertexShader, PixelShader* pixelShader);
	Mesh processMesh(Graphics* graphics, const aiScene* scene, aiMesh* mesh, VertexShader* vertexShader, PixelShader* pixelShader);
};

