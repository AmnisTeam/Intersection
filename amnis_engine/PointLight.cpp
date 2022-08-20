#include "pch.h"
#include "PointLight.h"
#include "RenderWindow.h"
#include "ModeledObject.h"

PointLight::PointLight(RenderWindow* renderWindow, AmnModel* model, bool bind)
{
	this->model = new ModeledObject(renderWindow, model, renderWindow->graphics->defaultVS, renderWindow->graphics->lightPS);

	if (bind)
		this->bind(renderWindow);
	this->renderWindow = renderWindow;

	this->model->PSConstBufAdd(5);
	this->model->PSConstBufAddValue(5, &color, "Color", sizeof(color));
	this->model->PSConstBufAddValue(5, &turnedOn, "TurnedOn", sizeof(float4));
	this->model->PSConstBufInit(5);
}

PointLight::PointLight(RenderWindow* renderWindow, AmnModel* model, float3 positoin, float4 color, bool bind)
{
	this->model = new ModeledObject(renderWindow, model, renderWindow->graphics->defaultVS, renderWindow->graphics->lightPS);

	if (bind)
		this->bind(renderWindow);
	this->renderWindow = renderWindow;

	this->model->PSConstBufAdd(5);
	this->model->PSConstBufAddValue(5, &color, "Color", sizeof(color));
	this->model->PSConstBufAddValue(5, &turnedOn, "TurnedOn", sizeof(float4));
	this->model->PSConstBufInit(5);

	setPosition(positoin);
	setColor(color);
}

PointLight::~PointLight()
{
	delete model;
}

void PointLight::bind(RenderWindow* renderWindow)
{
	renderWindow->graphics->pointLights2.push_back(this);
	renderWindow->graphics->updatePointLights();
}

void PointLight::setPosition(float3 position)
{
	Transformable::setPosition(position);
	renderWindow->graphics->updatePointLights();
}

void PointLight::setColor(float4 color)
{
	this->color = color;
	renderWindow->graphics->updatePointLights();
}

void PointLight::setFactors(float3 factors)
{
	kc = factors.x;
	kl = factors.y;
	kq = factors.z;
	renderWindow->graphics->updatePointLights();
}

void PointLight::setParams(float3 position, float4 color, float3 factors)
{
	Transformable::setPosition(position);
	this->color = color;
	kc = factors.x;
	kl = factors.y;
	kq = factors.z;
	renderWindow->graphics->updatePointLights();
}

void PointLight::turn(bool on)
{
	turnedOn = on;
	renderWindow->graphics->updatePointLights();
}

void PointLight::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	this->model->PSConstBufUpdateValue(5, 0, &color);
	this->model->PSConstBufUpdateValue(5, 1, &turnedOn);
	renderTarget->draw(model, state);
}