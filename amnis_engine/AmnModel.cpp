#include "pch.h"
#include "AmnModel.h"
#include "RenderWindow.h"

AmnModel::AmnModel(RenderWindow* const renderWindow, std::vector<Vertex> const vertices, std::vector<int> const indices, VertexShader* vertexShader, PixelShader* pixelShader)
{
	this->renderWindow = renderWindow;
	Mesh* mesh = new Mesh(renderWindow, vertices, indices, vertexShader, pixelShader);
	meshes.push_back(*mesh);
}

AmnModel::AmnModel(RenderWindow* const renderWindow, char* modelPath)
{
	this->renderWindow = renderWindow;
	loadModel(renderWindow, modelPath, new DefaultVertexShader(renderWindow->graphics, L"VertexShader.hlsl"), new PixelShader(renderWindow->graphics, L"PixelShader.hlsl"));
}

AmnModel::AmnModel(RenderWindow* const renderWindow, char* modelPath, VertexShader* vertexShader, PixelShader* pixelShader)
{
	this->renderWindow = renderWindow;
	loadModel(renderWindow, modelPath, vertexShader, pixelShader);
}

void AmnModel::setTexture(Texture* texture, unsigned int slot)
{
	textures[slot] = texture;
}

std::vector<Texture*> AmnModel::loadMaterialTextures(RenderWindow* const renderWindow, aiMaterial* mat, aiTextureType type)
{
	std::vector<Texture*> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		std::string path;

		if (extension.compare("fbx") == 0)
		{
			path = directory.substr( 0, directory.find_last_of('\\')) + "\\";
			//path = path.substr(0, path.find_last_of('\\')) + "\\textures\\";

			std::string inputPath = str.C_Str();
			//inputPath = inputPath.substr(inputPath.find_last_of('\\') + 1, inputPath.size());
			path += inputPath;
		}
		else
		{
			path = directory + str.C_Str();
		}

		size_t cSize = strlen(path.c_str()) + 1;
		if (cSize > 1)
			int point = 0;
		wchar_t* texFileNameWChar = new wchar_t[cSize];
		MultiByteToWideChar(0, 0, path.c_str(), cSize, texFileNameWChar, cSize);

		Texture* texture = new Texture(renderWindow->graphics, texFileNameWChar);
		textures.push_back(texture);

		delete[cSize] texFileNameWChar;
	}
	return textures;
}

void AmnModel::draw(RenderTarget* renderTarget, RenderState renderState)
{
	for (auto it = textures.begin(); it != textures.end(); it++)
		it->second->bind(it->first);

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].drawDepthStencil = drawDepthStencil;
		meshes[i].draw(renderTarget, renderState);
	}
}

void AmnModel::loadModel(RenderWindow* const renderWindow, std::string path, VertexShader* vertexShader, PixelShader* pixelShader)
{
	extension = path.substr(path.find_last_of('.') + 1, path.size());
	if (/*extension.compare("fbx") == 0*/false)
	{
	}
	else
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_ConvertToLeftHanded |
			aiProcess_RemoveRedundantMaterials |
			aiProcess_PreTransformVertices |
			aiProcess_GenUVCoords |
			aiProcess_OptimizeMeshes);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			throw;
		//cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		directory = path.substr(0, path.find_last_of('\\')) + "\\";
		processNode(renderWindow, scene->mRootNode, scene, vertexShader, pixelShader);
	}
}

void AmnModel::processNode(RenderWindow* const renderWindow, aiNode* node, const aiScene* scene, VertexShader* vertexShader, PixelShader* pixelShader)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(renderWindow, scene, mesh, vertexShader, pixelShader));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(renderWindow, node->mChildren[i], scene, vertexShader, pixelShader);
}

Mesh AmnModel::processMesh(RenderWindow* const renderWindow, const aiScene* scene, aiMesh* mesh, VertexShader* vertexShader, PixelShader* pixelShader)
{
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	int upAxis = 0;
	scene->mMetaData->Get<int>("UpAxis", upAxis);
	int upAxisSign = 1;
	scene->mMetaData->Get<int>("UpAxisSign", upAxisSign);

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex{};
		vertex.pos.x = mesh->mVertices[i].x;
		if (upAxis && false)
		{
			vertex.pos.y = -mesh->mVertices[i].z;
			vertex.pos.z = mesh->mVertices[i].y;
		}
		else
		{
			vertex.pos.y = mesh->mVertices[i].y;
			vertex.pos.z = mesh->mVertices[i].z;
		}

		if (mesh->mNormals)
		{
			vertex.normal.x = mesh->mNormals[i].x;
			vertex.normal.y = mesh->mNormals[i].y;
			vertex.normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mTangents)
		{
			vertex.tangent.x = mesh->mTangents[i].x;
			vertex.tangent.y = mesh->mTangents[i].y;
			vertex.tangent.z = mesh->mTangents[i].z;
		}
		if (mesh->mBitangents)
		{
			vertex.bitangent.x = mesh->mBitangents[i].x;
			vertex.bitangent.y = mesh->mBitangents[i].y;
			vertex.bitangent.z = mesh->mBitangents[i].z;
		}

		if (mesh->mTextureCoords[0])
		{
			vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		vertices.push_back(vertex);
	}
	
	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	Mesh outputMesh = Mesh(renderWindow, vertices, indices, vertexShader, pixelShader);

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		//int countAMBIENT = material->GetTextureCount(aiTextureType_AMBIENT);
		//int countAMBIENT_OCCLUSION = material->GetTextureCount(aiTextureType_AMBIENT_OCCLUSION);
		//int countBASE_COLOR = material->GetTextureCount(aiTextureType_BASE_COLOR);
		//int countCLEARCOAT = material->GetTextureCount(aiTextureType_CLEARCOAT);
		//int countDIFFUSE = material->GetTextureCount(aiTextureType_DIFFUSE);
		//int countDIFFUSE_ROUGHNESS = material->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS);
		//int countDISPLACEMENT = material->GetTextureCount(aiTextureType_DISPLACEMENT);
		//int countEMISSION_COLOR = material->GetTextureCount(aiTextureType_EMISSION_COLOR);
		//int countEMISSIVE = material->GetTextureCount(aiTextureType_EMISSIVE);
		//int countHEIGHT = material->GetTextureCount(aiTextureType_HEIGHT);
		//int countLIGHTMAP = material->GetTextureCount(aiTextureType_LIGHTMAP);
		//int countMETALNESS = material->GetTextureCount(aiTextureType_METALNESS);
		//int countNONE = material->GetTextureCount(aiTextureType_NONE);
		//int countNORMALS = material->GetTextureCount(aiTextureType_NORMALS);
		//int countNORMAL_CAMERA = material->GetTextureCount(aiTextureType_NORMAL_CAMERA);
		//int countOPACITY = material->GetTextureCount(aiTextureType_OPACITY);
		//int countREFLECTION = material->GetTextureCount(aiTextureType_REFLECTION);
		//int countSHEEN = material->GetTextureCount(aiTextureType_SHEEN);
		//int countSHININESS = material->GetTextureCount(aiTextureType_SHININESS);
		//int countSPECULAR = material->GetTextureCount(aiTextureType_SPECULAR);
		//int countTRANSMISSION = material->GetTextureCount(aiTextureType_TRANSMISSION);
		//int countUNKNOWN = material->GetTextureCount(aiTextureType_UNKNOWN);
		//int countForce32Bit = material->GetTextureCount(_aiTextureType_Force32Bit);

		//if (countAMBIENT > 0 || countAMBIENT_OCCLUSION > 0 || countBASE_COLOR > 0 || countCLEARCOAT > 0 || countDIFFUSE > 0 || countDIFFUSE_ROUGHNESS > 0 || countDISPLACEMENT > 0 || countEMISSION_COLOR > 0 || countEMISSIVE > 0 || countHEIGHT > 0 || countLIGHTMAP > 0 || countMETALNESS > 0 || countNONE > 0 || countNORMALS > 0 || countNORMAL_CAMERA > 0 || countOPACITY > 0 || countREFLECTION > 0 || countSHEEN > 0 || countSHININESS > 0 || countSPECULAR > 0 || countTRANSMISSION > 0 || countUNKNOWN > 0 || countForce32Bit > 0)
		//{
		//	int k =	 0;
		//}

		std::vector<Texture*> texturesDiffuse = loadMaterialTextures(renderWindow, material, aiTextureType_DIFFUSE);
		std::vector<Texture*> texturesBaseColor = loadMaterialTextures(renderWindow, material, aiTextureType_BASE_COLOR);
		std::vector<Texture*> texturesNormals = loadMaterialTextures(renderWindow, material, aiTextureType_NORMALS);

		if (texturesDiffuse.size() > 0)
			outputMesh.textures[0] = texturesDiffuse[0];


		if (texturesBaseColor.size() > 0)
			outputMesh.textures[0] = texturesBaseColor[0];

		if (texturesNormals.size() > 0)
			outputMesh.textures[1] = texturesNormals[0];
	}
	return outputMesh;
}