#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "Camera.h"
#include <vector>
#include "Transformable.h"

class RenderWindow;
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
	DECL AmnModel(RenderWindow* renderWindow, std::vector<Vertex> const vertices, std::vector<int> const indices, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL AmnModel(RenderWindow* const renderWindow, char* modelPath);
	DECL AmnModel(RenderWindow* const renderWindow, char* modelPath, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void setTexture(Texture* texture, unsigned int slot);
	DECL std::vector<Texture*> loadMaterialTextures(RenderWindow* const renderWindow, aiMaterial* mat, aiTextureType type);
	DECL void draw(RenderTarget* renderTarget, RenderState renderState);
private:
	RenderWindow* renderWindow;
	std::vector<Mesh> meshes;
	std::string directory;
	DECL void loadModel(RenderWindow* const renderWindow, std::string path, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void processNode(RenderWindow* const renderWindow, aiNode* node, const aiScene* scene, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL Mesh processMesh(RenderWindow* const renderWindow, const aiScene* scene, aiMesh* mesh, VertexShader* vertexShader, PixelShader* pixelShader);
};

