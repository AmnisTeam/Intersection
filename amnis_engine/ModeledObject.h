#pragma once
#include "IDrawable.h"
#include "Transformable.h"
#include "Texture.h"
#include "AmnModel.h"
#include "ConstantBuffersSystem.h"
#include <vector>
#include "decl.h"

class AmnModel;
class RenderWindow;

class ModeledObject : public Transformable, public IDrawable
{
public:
	RenderWindow* renderWindow;
	ConstantBuffersSystem* constantBuffersSystem;
	DECL ModeledObject(RenderWindow* const renderWindow, AmnModel* const model);
	DECL ModeledObject(RenderWindow* const renderWindow, AmnModel* const model, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL ~ModeledObject();
	DECL void setModel(AmnModel* model);
	DECL AmnModel* getModel() const;
	DECL void setTexture(Texture* const texture, const unsigned int slot);
	DECL void setVertexShader(VertexShader* vertexShader);
	DECL void setPixelShader(PixelShader* pixelShader);
	DECL virtual void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	AmnModel* model;
	std::map<unsigned int, Texture*> textures;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	DECL void bindAllTextures();
	DECL void constructor(RenderWindow* const renderWindow, AmnModel* const model, VertexShader* vertexShader, PixelShader* pixelShader);
};