#pragma once
#include "IDrawable.h"
#include "Transformable.h"
#include "Texture.h"
#include "AmnModel.h"
#include <vector>
#include "decl.h"

class AmnModel;
class RenderWindow;

class ModeledObject : public Transformable, public IDrawable
{
public:
	RenderWindow* renderWindow;
	DECL ModeledObject(RenderWindow* const renderWindow, AmnModel* const model);
	DECL ModeledObject(RenderWindow* const renderWindow, AmnModel* const model, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL ~ModeledObject();
	DECL void setModel(AmnModel* model);
	DECL AmnModel* getModel() const;
	DECL void setTexture(Texture* const texture, const unsigned int slot);
	DECL void setVertexShader(VertexShader* vertexShader);
	DECL void setPixelShader(PixelShader* pixelShader);
	DECL virtual void draw(RenderTarget* renderTarget, RenderState state) override;

	DECL void VSConstBufSet(ConstantBuffer* constantBuffer, unsigned int const slot);
	DECL void PSConstBufSet(ConstantBuffer* constantBuffer, unsigned int const slot);
	DECL void VSConstBufAdd(unsigned int const slot);
	DECL void PSConstBufAdd(unsigned int const slot);
	DECL void VSConstBufAddValue(unsigned int slot, void* value, const char* key, unsigned int const size);
	DECL void PSConstBufAddValue(unsigned int slot, void* value, const char* key, unsigned int const size);
	DECL void VSConstBufUpdateValue(unsigned int const slot, unsigned int dataID, void* data);
	DECL void PSConstBufUpdateValue(unsigned int const slot, unsigned int dataID, void* data);
	DECL void VSConstBufInit(unsigned int const slot);
	DECL void PSConstBufInit(unsigned int const slot);
private:
	AmnModel* model;
	std::map<unsigned int, Texture*> textures;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	DECL void bindAllTextures();
	DECL void constructor(RenderWindow* const renderWindow, AmnModel* const model, VertexShader* vertexShader, PixelShader* pixelShader);
};