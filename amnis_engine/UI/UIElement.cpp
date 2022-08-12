#include "pch.h"
#include "UIElement.h"
#include "../RenderWindow.h"

UIElement::UIElement(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader)
{
    this->renderWindow = renderWindow;

    vertices.push_back({ { -1, -1, 0 }, { 0, 1 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}});
    vertices.push_back({ { -1, 1, 0 }, { 0, 0 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}});
    vertices.push_back({ { 1, 1, 0 }, { 1, 0 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}});
    vertices.push_back({ { 1, -1, 0 }, { 1, 1 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}});

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);

    indices.push_back(3);
    indices.push_back(1);
    indices.push_back(2);

    quadModel = new AmnModel(renderWindow->graphics, vertices, indices, vertexShader, pixelShader);
    quad = new ModeledObject(renderWindow, quadModel, vertexShader, pixelShader);
    quad->PSConstBufAdd(0);
    quad->PSConstBufAddValue(0, &color, "Color", sizeof(color));
    quad->PSConstBufInit(0);
    setPosition({0, 0, 1});
}

UIElement::UIElement(RenderWindow* renderWindow, AmnModel* model, VertexShader* vertexShader, PixelShader* pixelShader)
{
    this->renderWindow = renderWindow;
    quad = new ModeledObject(renderWindow, model);
    setRotation({ -PI * 0.5f, 0, 0 });
    setPosition({ 0, 0, 1 });
}

void UIElement::draw(RenderTarget* renderTarget, RenderState state)
{
    state.modelMatrix = modelMatrix * state.modelMatrix;
    quad->PSConstBufUpdateValue(0, 0, &color);
    renderTarget->draw(quad, state);
}
