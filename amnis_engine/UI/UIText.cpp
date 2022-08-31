#include "pch.h"
#include "UIText.h"

UIText::UIText(RenderWindow* renderWindow, unsigned int const max_chars_count, VertexShader* vertexShader, PixelShader* pixelShader) 
	: UIElement(renderWindow)
{
	text = new Text(renderWindow, max_chars_count, vertexShader, pixelShader);
	initColorSystem(text->textFrame, 0);
}

UIText::~UIText()
{
	delete text;
}

void UIText::setSizeInPixels(float2 size)
{
	UIElement::setSizeInPixels(size);
}

void UIText::update(RenderTarget* renderTarget, RenderState state)
{
	UIElement::update(renderTarget, state);
}

void UIText::draw(RenderTarget* renderTarget, RenderState state)
{
	update(renderTarget, state);
	state.modelMatrix = modelMatrix * state.modelMatrix;

	float3 scale = float3{ DirectX::XMVectorGetX(state.modelMatrix.r[0]), DirectX::XMVectorGetY(state.modelMatrix.r[1]), DirectX::XMVectorGetZ(state.modelMatrix.r[2]) };
	text->modelScale = float2{ scale.x / scale.y, 1};
	text->textFrame->constantBuffersSystem->PSUpdateValue(1, "ModelScale", &text->modelScale);

	renderTarget->draw(text, state);
}
