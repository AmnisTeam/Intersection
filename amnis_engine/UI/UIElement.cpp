#include "pch.h"
#include "UIElement.h"
#include "../RenderWindow.h"

UIElement::UIElement(RenderWindow* renderWindow)
{
    this->renderWindow = renderWindow;
    quad = new ModeledObject(renderWindow, renderWindow->modelsContent->plane, renderWindow->graphics->shadersContent->defaultVS, renderWindow->graphics->shadersContent->onlyTexturePS);
    setRotation({-PI * 0.5f, 0, 0});
    setPosition({0, 0, 1});
}

void UIElement::draw(RenderTarget* renderTarget, RenderState state)
{
    state.modelMatrix = modelMatrix * state.modelMatrix;
    renderTarget->draw(quad, state);
}
