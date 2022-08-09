#pragma once
//#include "Model.h"
#include <d3d11.h>
#include "RenderState.h"
#include "decl.h"

class IDrawable;
class AmnModel;

class RenderTarget
{
public:
	ID3D11RenderTargetView* renderTarget;
	DECL RenderTarget();
	DECL void draw(AmnModel* model, RenderState state);
	DECL void draw(IDrawable* drawable, RenderState renderState);
};