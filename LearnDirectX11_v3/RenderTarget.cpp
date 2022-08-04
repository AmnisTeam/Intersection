#include "RenderTarget.h"
#include "Model.h"
#include "RenderWindow.h"

RenderTarget::RenderTarget()
{

}

void RenderTarget::draw(Model* model, RenderState state)
{
	model->draw(state.renderWindow->graphics, state.renderWindow->boundCamera, state.modelMatrix);
}

void RenderTarget::draw(IDrawable* drawable, RenderState state)
{
	drawable->draw(this, state);
}