#pragma once
//#include "Model.h"
#include <d3d11.h>
#include "RenderState.h"

class IDrawable;
class Model;

class RenderTarget
{
public:
	ID3D11RenderTargetView* renderTarget;
	RenderTarget();
	void draw(Model* model, RenderState state);
	void draw(IDrawable* drawable, RenderState renderState);
};