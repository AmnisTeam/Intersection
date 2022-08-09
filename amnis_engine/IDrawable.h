#pragma once
#include "RenderState.h"
#include "RenderTarget.h"
#include "decl.h"

class IDrawable
{
public:
	DECL virtual void draw(RenderTarget* renderTarget, RenderState state) = 0;
};