#pragma once
#include "../IDrawable.h"
#include "../Transformable.h"
#include "../decl.h"
#include "../ModeledObject.h"
#include "UIStyle.h"

class UIElement : public Transformable, public IDrawable
{
public:
	ModeledObject* quad;
	double width;
	double height;

	float4 color = {1, 1, 1, 1};
	float4 hoverColor = { 1, 1, 1, 1 };
	float4 pressColor = { 1, 1, 1, 1 };
	float4 onColor = { 1, 1, 1, 1 };
	float4 onHoverColor = { 1, 1, 1, 1 };
	float4 onPressColor = { 1, 1, 1, 1 };

	DECL UIElement(RenderWindow* renderWindow, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL UIElement(RenderWindow* renderWindow, AmnModel* model, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL void setPositionInPixels(float2 position);
	DECL void setSizeInPixels(float2 size);
	DECL float2 getSizeInPixels() const;
	DECL float2 getPositionInPixels() const;
	DECL bool getHover() const;
	DECL bool getPressed() const;
	DECL bool onDown();
	DECL bool onUp();
	DECL virtual void updateColor();
	DECL void setStyle(UIStyle style);
	virtual void DECL update(RenderTarget* renderTarget, RenderState state);
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
protected:
	RenderWindow* renderWindow;
	AmnModel* quadModel;
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	float2 sizeInPixels = {0, 0};
	float2 positionInPixels = {0, 0};
	RECT oldClientRect = {};
	DECL void setPositionInPixels(float2 position, RECT clientRect);
	DECL void setSizeInPixels(float2 size, RECT clientRect);
};

