#include "pch.h"
#include "RenderTarget.h"
#include "AmnModel.h"
#include "RenderWindow.h"
#include "IDrawable.h"

RenderTarget::RenderTarget()
{

}

void RenderTarget::draw(AmnModel* model, RenderState state)
{
	//model->draw(state.renderWindow->graphics, state.renderWindow->boundCamera, state.modelMatrix);
	state.modelMatrix = model->modelMatrix * state.modelMatrix;
	model->draw(this, state);
}

void RenderTarget::draw(IDrawable* drawable, RenderState state)
{
	drawable->draw(this, state);
}
