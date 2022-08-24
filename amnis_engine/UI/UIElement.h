#pragma once
#include "../IDrawable.h"
#include "../Transformable.h"
#include "../decl.h"
#include "../ModeledObject.h"
#include "UIStyle.h"
#include "../VertexShader.h"
#include "../PixelShader.h"
#include "../InnerModelsContent.h"

class UIElement : public Transformable, public IDrawable
{
public:
	float4 color = { 1, 1, 1, 1 };
	float4 hoverColor = { 1, 1, 1, 1 };
	float4 pressColor = { 1, 1, 1, 1 };
	float4 onColor = { 1, 1, 1, 1 };
	float4 onHoverColor = { 1, 1, 1, 1 };
	float4 onPressColor = { 1, 1, 1, 1 };

	DECL UIElement(RenderWindow* renderWindow);
	DECL void setPositionInPixels(float2 position);
	DECL virtual void setSizeInPixels(float2 size);
	DECL virtual void setSizeInScreenSize(float2 size);
	DECL float2 getSizeInPixels() const;
	DECL float2 getPositionInPixels() const;
	DECL float2 getScreenPosition() const;
	DECL void setPivot(float2 pivot);
	DECL float2 getPivot() const;
	DECL void setAnchor(float2 anchor);
	DECL float2 getAnchor() const;
	DECL bool getHover() const;
	DECL bool getPressed() const;
	DECL bool onDown();
	DECL bool onUp();
	DECL void initColorSystem(ModeledObject* object);
	DECL virtual void updateColor();
	DECL void setStyle(UIStyle style);
	DECL static void setStaticVertexAndPixelShaders(VertexShader* vertexShader, PixelShader* pixelShader);
	virtual void DECL update(RenderTarget* renderTarget, RenderState state);
protected:

	RenderWindow* renderWindow;
	ModeledObject* coloredModel;
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	static VertexShader* defaultVS;
	static PixelShader* defaultPS;
	float2 sizeInPixels = { 0, 0 };
	float2 positionInPixels = { 0, 0 };
	float2 screenPosition = { 0, 0 };
	float2 pivot = { 0.5f, 0.5f };
	float2 anchor = { 0, 0 };
	RECT firstClientRect = {};
	RECT oldClientRect = {};

	DECL UIElement();
	DECL void _constructor(RenderWindow* renderWindow);
	DECL void setPositionInPixels(float2 position, RECT clientRect);
	DECL void setSizeInPixels(float2 size, RECT clientRect);
	DECL void setRenderWindow(RenderWindow* renderWindow);
	DECL void setFirstClientRect();
};