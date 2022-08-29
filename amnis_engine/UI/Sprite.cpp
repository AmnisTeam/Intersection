#include "pch.h"
#include "Sprite.h"

Sprite::Sprite(RenderWindow* renderWindow, Texture* texture, float4 textureRect, VertexShader* vertexShader, PixelShader* pixelShader) : UIElement(renderWindow)
{
	square = new ModeledObject(renderWindow, InnerModelsContent::square, vertexShader, pixelShader);
	initColorSystem(square, 0);
	//setSprite(texture, textureRect);
}

void Sprite::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = state.modelMatrix * modelMatrix;
	update(renderTarget, state);

	renderTarget->draw(square, state);
}