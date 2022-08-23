#pragma once
#include "Transformable.h"
#include "IDrawable.h"

class Terrain : public Transformable, public IDrawable
{
public:

	Terrain();

	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
};

