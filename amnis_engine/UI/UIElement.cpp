#include "pch.h"
#include "UIElement.h"
#include "../RenderWindow.h"

VertexShader* UIElement::defaultVS;
PixelShader* UIElement::defaultPS;

UIElement::UIElement(RenderWindow* renderWindow)
{
    _constructor(renderWindow);
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

void UIElement::setSizeInScreenSize(float2 size)
{
    setScale({ size.x / renderWindow->boundCamera->aspect / renderWindow->boundCamera->angle, size.y / renderWindow->boundCamera->angle, getScale().z});
}

float2 UIElement::getSizeInPixels() const
{
    return sizeInPixels;
}

float2 UIElement::getPositionInPixels() const
{
    return positionInPixels;
}

float2 UIElement::getScreenPosition() const
{
    return screenPosition;
}

void UIElement::setPivot(float2 pivot)
{
    this->pivot = pivot;
    setPositionInPixels(getPositionInPixels());
}

float2 UIElement::getPivot() const
{
    return pivot;
}

void UIElement::setAnchor(float2 anchor)
{
    this->anchor = anchor;
}

float2 UIElement::getAnchor() const
{
    return anchor;
}

bool UIElement::getHover() const
{
    float2 mousePos = renderWindow->window->mousePos;

    float2 uiElementPos =  screenPosition;
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

void UIElement::initColorSystem(ModeledObject* object)
{
    coloredModel = object;
    object->PSConstBufAdd(0);
    object->PSConstBufAddValue(0, &color, "Color", sizeof(color));
    object->PSConstBufInit(0);
}

void UIElement::updateColor()
{
    if (getPressed())
    {
        coloredModel->PSConstBufUpdateValue(0, 0, &pressColor);
    }
    else
    {
        if (getHover())
            coloredModel->PSConstBufUpdateValue(0, 0, &hoverColor);
        else
            coloredModel->PSConstBufUpdateValue(0, 0, &color);
    }
}

void UIElement::setStyle(UIStyle style)
{
    color = style.color;
    hoverColor = style.hoverColor;
    pressColor = style.pressColor;
    onColor = style.onColor;
    onHoverColor = style.onHoverColor;
    onPressColor = style.onPressColor;
}

void UIElement::setStaticVertexAndPixelShaders(VertexShader* vertexShader, PixelShader* pixelShader)
{
    defaultVS = vertexShader;
    defaultPS = pixelShader;
}

UIElement::UIElement()
{
}

void UIElement::_constructor(RenderWindow* renderWindow)
{
    setRenderWindow(renderWindow);
    setPosition({ 0, 0, 1 });

    setFirstClientRect();

    setPivot(pivot);
    setPositionInPixels({ firstClientRect.right * 0.5f, firstClientRect.bottom * 0.5f });
    setSizeInPixels({ 100, 100 });
}

void UIElement::setPositionInPixels(float2 position, RECT clientRect)
{
    positionInPixels = position;

    float width = clientRect.right;
    float height = clientRect.bottom;

    float2 elementSize = getSizeInPixels();
    float2 clientChanging = { firstClientRect.right - width, firstClientRect.bottom - height };

    float2 screenPosition = float2
    {
        firstClientRect.right * anchor.x + position.x + elementSize.x * 0.5f - elementSize.x * pivot.x - clientChanging.x * anchor.x,
        firstClientRect.bottom * anchor.y + position.y + elementSize.y * 0.5f - elementSize.y * pivot.y - clientChanging.y * anchor.y
    };

    this->screenPosition = screenPosition;

    float2 normalizedPosition = { (screenPosition.x / width) * 2 - 1, 1 - (screenPosition.y / height) * 2 };
    setPosition(float3{ normalizedPosition.x / renderWindow->boundCamera->aspect / renderWindow->boundCamera->angle, normalizedPosition.y / renderWindow->boundCamera->angle, getPosition().z });
}

void UIElement::setSizeInPixels(float2 size, RECT clientRect)
{
    sizeInPixels = size;

    float width = clientRect.right;
    float hegiht = clientRect.bottom;

    float onePixelX = 1.0f / width;
    float onePixelY = 1.0f / hegiht;

    setSizeInScreenSize(float2{ onePixelX * size.x, onePixelY * size.y });
}

void UIElement::setRenderWindow(RenderWindow* renderWindow)
{
    this->renderWindow = renderWindow;
}

void UIElement::setFirstClientRect()
{
    RECT clientRect = {};
    GetClientRect(renderWindow->window->hwnd, &clientRect);
    firstClientRect = clientRect;
}

void UIElement::update(RenderTarget* renderTarget, RenderState state)
{
    RECT clientRect;
    GetClientRect(renderWindow->window->hwnd, &clientRect);

    if (oldClientRect != clientRect)
    {
        setPositionInPixels(positionInPixels, clientRect);
        setSizeInPixels(sizeInPixels);
        oldClientRect = clientRect;
    }

    updateColor();
}

