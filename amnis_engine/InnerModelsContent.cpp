#include "pch.h"
#include "InnerModelsContent.h"
#include "RenderWindow.h"

AmnModel* InnerModelsContent::square;
std::vector<Vertex> InnerModelsContent::vertices;
std::vector<int> InnerModelsContent::indices;

void InnerModelsContent::load(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader)
{
    initSquare(&vertices, &indices);
    square = new AmnModel(renderWindow->graphics, vertices, indices, vertexShader, pixelShader);
}

void InnerModelsContent::initSquare(std::vector<Vertex>* vertices, std::vector<int>* indices)
{
    vertices->clear();
    indices->clear();

    vertices->push_back({ { -1, -1, 0 }, { 0, 1 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });
    vertices->push_back({ { -1, 1, 0 }, { 0, 0 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });
    vertices->push_back({ { 1, 1, 0 }, { 1, 0 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });
    vertices->push_back({ { 1, -1, 0 }, { 1, 1 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });

    indices->push_back(0);
    indices->push_back(1);
    indices->push_back(3);

    indices->push_back(3);
    indices->push_back(1);
    indices->push_back(2);
}
