#pragma once
//#include "Model.h"
#include <d3d11.h>
#include "RenderState.h"
#include "decl.h"

class IDrawable;
class Model;

class RenderTarget
{
public:
	ID3D11RenderTargetView* renderTarget;
	DECL RenderTarget();
	DECL void draw(Model* model, RenderState state);
	DECL void draw(IDrawable* drawable, RenderState renderState);
};