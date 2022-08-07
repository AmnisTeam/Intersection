#include "pch.h"
#include "Sphere.h"

Sphere::Sphere(RenderWindow* renderWindow)
{
	this->renderWindow = renderWindow;
	Graphics* graphics = renderWindow->graphics;

	model = new ModeledObject(renderWindow, renderWindow->modelsContent->sphere);
	model->setTexture(graphics->texturesContent->stoneWallAlbedo, 0);
	model->setTexture(graphics->texturesContent->stoneWallNormalMap, 1);
}

RenderWindow* Sphere::getRenderWindow()
{
	return renderWindow;
}

void Sphere::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(model, state);
}
