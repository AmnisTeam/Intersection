#include "pch.h"
#include "FbxLoader.h"
#include "Mesh.h"

FbxManager* FbxLoader::fbxManager;

HRESULT FbxLoader::loadFbxModel(RenderWindow* renderWindow, const char* path, std::vector<Mesh>* meshes, VertexShader* vertexShader, PixelShader* pixelShader)
{
    if (!fbxManager)
    {
        fbxManager = FbxManager::Create();
        FbxIOSettings* pIOsettings = FbxIOSettings::Create(fbxManager, IOSROOT);
        fbxManager->SetIOSettings(pIOsettings);
    }

    FbxImporter* pImporter = FbxImporter::Create(fbxManager, "");
    FbxScene* pFbxScene = FbxScene::Create(fbxManager, "");

    bool bSuccess = pImporter->Initialize(path, -1, fbxManager->GetIOSettings());
    if (!bSuccess) {
        MessageBox(NULL, L"Не удалось загрузить 3D модель.", L"Ошибка", MB_ICONERROR);
        return E_FAIL;
    }

    bSuccess = pImporter->Import(pFbxScene);
    if (!bSuccess) return E_FAIL;

    pImporter->Destroy();
    FbxNode* pFbxRootNode = pFbxScene->GetRootNode();
 
    if (pFbxRootNode)
    {
        for (int i = 0; i < pFbxRootNode->GetChildCount(); i++)
        {
            FbxNode* pFbxChildNode = pFbxRootNode->GetChild(i);

            if (pFbxChildNode->GetNodeAttribute() == NULL)
                continue;

            FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();

            if (AttributeType != FbxNodeAttribute::eMesh)
                continue;

            FbxMesh* pMesh = (FbxMesh*)pFbxChildNode->GetNodeAttribute();

            std::vector<Vertex> vertices = std::vector<Vertex>();
            std::vector<int> indices = std::vector<int>();

            FbxVector4* pVertices = pMesh->GetControlPoints();

            //Загрузка индексов
            for (int j = 0; j < pMesh->GetPolygonCount(); j++)
            {
                int iNumVertices = pMesh->GetPolygonSize(j);

                for (int k = 0; k < 3; k++) {
                    //if (k <= iNumVertices)
                    //{
                        indices.push_back(pMesh->GetPolygonVertex(j, k));
                    //}
                    //else
                    //{
                     //   indices.push_back(0);
                    //}
                }
            }

            //Загрузка вертексов
            for (int i = 0; i < pMesh->GetControlPointsCount(); i++)
            {
                Vertex vertex = {};

                FbxVector4 vec;
                vec = pMesh->GetControlPointAt(i);

                vertex.pos.x = vec.mData[0];
                vertex.pos.z = vec.mData[1];
                vertex.pos.y = vec.mData[2];
                vertices.push_back(vertex);
            }

            Mesh mesh = Mesh(renderWindow, vertices, indices, vertexShader, pixelShader);
            meshes->push_back(mesh);
        }
    }
    return S_OK;
}
