#include "pch.h"
#include "ModeledObject.h"
#include "RenderWindow.h"

ModeledObject::ModeledObject(RenderWindow* const renderWindow, Model* const model)
{
	constructor(renderWindow, model, renderWindow->graphics->shadersContent->defaultVS, renderWindow->graphics->shadersContent->defaultPS);
}

ModeledObject::ModeledObject(RenderWindow* const renderWindow, Model* const model, VertexShader* vertexShader, PixelShader* pixelShader)
{
	constructor(renderWindow, model, vertexShader, pixelShader);
}

void ModeledObject::constructor(RenderWindow* const renderWindow, Model* const model, VertexShader* vertexShader, PixelShader* pixelShader)
{
	this->renderWindow = renderWindow;
	this->model = model;
	setVertexShader(vertexShader);
	setPixelShader(pixelShader);
}

ModeledObject::~ModeledObject()
{
	// nothing
}

void ModeledObject::setModel(Model* model)
{
	this->model = model;
}

Model* ModeledObject::getModel() const
{
	return model;
}

void ModeledObject::setTexture(Texture* const texture, const unsigned int slot)
{
	textures[slot] = texture;
}

void ModeledObject::setVertexShader(VertexShader* vertexShader)
{
	this->vertexShader = vertexShader;
}

void ModeledObject::setPixelShader(PixelShader* pixelShader)
{
	this->pixelShader = pixelShader;
}

void ModeledObject::bindAllTextures()
{
	for (auto it = textures.begin(); it != textures.end(); it++)
		it->second->bind(it->first);
}

void ModeledObject::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	bindAllTextures();
	vertexShader->setVertexShader(renderWindow->graphics);
	pixelShader->setPixelShader(renderWindow->graphics);
	renderTarget->draw(model, state);
}

