#pragma once
#include <vector>
#include <fbxsdk.h>
#include "mymath.h"
#include "RenderWindow.h"

class Mesh;

class FbxLoader
{
private:
	static FbxManager* fbxManager;
	
public:
	static HRESULT loadFbxModel(RenderWindow* renderWindow, const char* path, std::vector<Mesh>* meshes, VertexShader* vertexShader, PixelShader* pixelShader);
};

