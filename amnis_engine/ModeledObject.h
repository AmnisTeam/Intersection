#pragma once
#include "IDrawable.h"
#include "Transformable.h"
#include "Texture.h"
#include "Model.h"
#include <vector>
#include "decl.h"

class Model;
class RenderWindow;

class ModeledObject : public Transformable, public IDrawable
{
public:
	RenderWindow* renderWindow;
	DECL ModeledObject(RenderWindow* const renderWindow, Model* const model);
	DECL ModeledObject(RenderWindow* const renderWindow, Model* const model, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL ~ModeledObject();
	DECL void setModel(Model* model);
	DECL Model* getModel() const;
	DECL void setTexture(Texture* const texture, const unsigned int slot);
	DECL void setVertexShader(VertexShader* vertexShader);
	DECL void setPixelShader(PixelShader* pixelShader);
	//Texture* getTexture(const unsigned int slot) const;
	DECL virtual void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	Model* model;
	std::map<unsigned int, Texture*> textures;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	DECL void bindAllTextures();
	DECL void constructor(RenderWindow* const renderWindow, Model* const model, VertexShader* vertexShader, PixelShader* pixelShader);
};