#include "pch.h"
#include "ModeledObject.h"
#include "RenderWindow.h"

ModeledObject::ModeledObject(RenderWindow* const renderWindow, AmnModel* const model)
{
	constructor(renderWindow, model, renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);
}

ModeledObject::ModeledObject(RenderWindow* const renderWindow, AmnModel* const model, VertexShader* vertexShader, PixelShader* pixelShader)
{
	constructor(renderWindow, model, vertexShader, pixelShader);
}

void ModeledObject::constructor(RenderWindow* const renderWindow, AmnModel* const model, VertexShader* vertexShader, PixelShader* pixelShader)
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

void ModeledObject::setModel(AmnModel* model)
{
	this->model = model;
}

AmnModel* ModeledObject::getModel() const
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

void ModeledObject::PSConstBufSet(ConstantBuffer* constantBuffer, unsigned int const slot)
{
	model->PSConstBufSet(constantBuffer, slot);
}

void ModeledObject::VSConstBufAdd(unsigned int const slot)
{
	model->VSConstBufAdd(slot);
}

void ModeledObject::PSConstBufAdd(unsigned int const slot)
{
	model->PSConstBufAdd(slot);
}

void ModeledObject::VSConstBufAddValue(unsigned int slot, void* value, const char* key, unsigned int const size)
{
	model->VSConstBufAddValue(slot, value, key, size);
}

void ModeledObject::PSConstBufAddValue(unsigned int slot, void* value, const char* key, unsigned int const size)
{
	model->PSConstBufAddValue(slot, value, key, size);
}

void ModeledObject::VSConstBufSet(ConstantBuffer* constantBuffer, unsigned int const slot)
{
	model->VSConstBufSet(constantBuffer, slot);
}

void ModeledObject::VSConstBufUpdateValue(unsigned int const slot, unsigned int dataID, void* data)
{
	model->VSConstBufUpdateValue(slot, dataID, data);
}

void ModeledObject::PSConstBufUpdateValue(unsigned int const slot, unsigned int dataID, void* data)
{
	model->PSConstBufUpdateValue(slot, dataID, data);
}

void ModeledObject::VSConstBufInit(unsigned int const slot)
{
	model->VSConstBufInit(slot);
}

void ModeledObject::PSConstBufInit(unsigned int const slot)
{
	model->PSConstBufInit(slot);
}

void ModeledObject::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	bindAllTextures();
	vertexShader->setVertexShader(renderWindow->graphics);
	pixelShader->setPixelShader(renderWindow->graphics);
	renderTarget->draw(model, state);
}

