#include "Sphere.h"
#include "TexturesContent.h"

Sphere::Sphere(RenderWindow* renderWindow)
{
	this->renderWindow = renderWindow;
	Graphics* graphics = renderWindow->graphics;

	model = new ModeledObject(renderWindow, ModelsContent::sphere);
	model->setTexture(TexturesContent::stoneWallAlbedo, 0);
	model->setTexture(TexturesContent::stoneWallNormalMap, 1);
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
