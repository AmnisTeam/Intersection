#include "pch.h"
#include "SkySphere.h"
#include "ShadersContent.h"


SkySphere::SkySphere(RenderWindow* renderWindow, Texture* texture)
{
	this->renderWindow = renderWindow;
	sphere = new Sphere(renderWindow);
	sphere->model->setPixelShader(ShadersContent::skyPS);
	sphere->model->setTexture(texture, 0);
	sphere->setScale({-5, -5, -5});
	sphere->setPosition(renderWindow->boundCamera->position);
}

SkySphere::~SkySphere()
{
	delete sphere;
}

void SkySphere::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	sphere->setPosition(renderWindow->boundCamera->position);
	renderTarget->draw(sphere, state);
}