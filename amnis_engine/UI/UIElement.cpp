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

    RECT clientRect = {};
    GetClientRect(renderWindow->window->hwnd, &clientRect);
    oldClientRect = clientRect;

    setPositionInPixels({ clientRect.right / 2.0f, clientRect.bottom / 2.0f});
    setSizeInPixels({100, 100});
}

UIElement::UIElement(RenderWindow* renderWindow, AmnModel* model, VertexShader* vertexShader, PixelShader* pixelShader)
{
    this->renderWindow = renderWindow;
    quad = new ModeledObject(renderWindow, model);
    setRotation({ -PI * 0.5f, 0, 0 });
    setPosition({ 0, 0, 1 });
}

void UIElement::setPositionInPixels(float2 position)
{
    RECT clientRect;
    GetClientRect(renderWindow->window->hwnd, &clientRect);
    setPositionInPixels(position, clientRect);
}

void UIElement::setSizeInPixels(float2 size)
{
    RECT clientRect;
    GetClientRect(renderWindow->window->hwnd, &clientRect);
    setSizeInPixels(size, clientRect);
}

float2 UIElement::getSizeInPixels() const
{
    return sizeInPixels;
}

float2 UIElement::getPositionInPixels() const
{
    return positionInPixels;
}

bool UIElement::getHover() const
{
    float2 mousePos = renderWindow->window->mousePos;
    float2 uiElementPos =  positionInPixels;
    float2 uiElementSize = sizeInPixels;

    float leftEdge = uiElementPos.x - uiElementSize.x * 0.5f;
    float rightEdge = uiElementPos.x + uiElementSize.x * 0.5f;
    float topEdge = uiElementPos.y - uiElementSize.y * 0.5f;
    float bottomEdge = uiElementPos.y + uiElementSize.y * 0.5f;

    if (mousePos.x >= leftEdge && mousePos.x <= rightEdge)
        if (mousePos.y <= bottomEdge && mousePos.y >= topEdge)
            return true;

    return false;
}

bool UIElement::getPressed() const
{
    if (getHover() && renderWindow->window->rawMouseLeftButtonPressed)
        return true;
    return false;
}

bool UIElement::onDown()
{
    if (getHover() && renderWindow->window->rawMouseLeftButtonDown)
        return true;
    return false;

}

bool UIElement::onUp()
{
    if (getHover() && renderWindow->window->rawMouseLeftButtonUp)
        return true;
    return false;
}

void UIElement::setPositionInPixels(float2 position, RECT clientRect)
{
    positionInPixels = position;

    float width = clientRect.right;
    float hegiht = clientRect.bottom;

    float2 normalizedPosition = { (position.x / width) * 2 - 1, 1 - (position.y / hegiht) * 2 };
    setPosition(float3{ normalizedPosition.x, normalizedPosition.y, getPosition().z });
}

void UIElement::setSizeInPixels(float2 size, RECT clientRect)
{
    sizeInPixels = size;

    float width = clientRect.right;
    float hegiht = clientRect.bottom;

    float onePixelX = 1.0f / width;
    float onePixelY = 1.0f / hegiht;

    setScale(float3{ onePixelX * size.x, onePixelY * size.y, getScale().z });
}

void UIElement::update(RenderTarget* renderTarget, RenderState state)
{
    RECT clientRect;
    GetClientRect(renderWindow->window->hwnd, &clientRect);

    if (oldClientRect != clientRect)
        setPositionInPixels(positionInPixels, clientRect);

    if (getPressed())
    {
        quad->PSConstBufUpdateValue(0, 0, &pressColor);
    }
    else
    {
        int k = 5;
        if (getHover())
            quad->PSConstBufUpdateValue(0, 0, &hoverColor);
        else
            quad->PSConstBufUpdateValue(0, 0, &color);
    }
}

void UIElement::draw(RenderTarget* renderTarget, RenderState state)
{
    update(renderTarget, state);
    renderTarget->draw(quad, state);
}

