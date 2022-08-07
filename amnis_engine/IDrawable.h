#pragma once
#include "RenderState.h"
#include "RenderTarget.h"

class IDrawable
{
public:
	virtual void draw(RenderTarget* renderTarget, RenderState state) = 0;
};