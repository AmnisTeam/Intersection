#include "pch.h"
#include "UIText.h"

UIText::UIText(RenderWindow* renderWindow, unsigned int const max_chars_count, VertexShader* vertexShader, PixelShader* pixelShader) 
	: UIElement(renderWindow)
{
	text = new Text(renderWindow, max_chars_count, vertexShader, pixelShader);
}

UIText::~UIText()
{
	delete text;
}

void UIText::setSizeInPixels(float2 size)
{
	UIElement::setSizeInPixels(size);
}

void UIText::setSizeInScreenSize(float2 size)
{
	UIElement::setSizeInScreenSize(size);
	text->modelScale = { text->getScale().x * getScale().x, text->getScale().y * getScale().y };
	text->textFrame->PSConstBufUpdateValue(1, 2, &text->modelScale);
}

void UIText::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(text, state);
}
