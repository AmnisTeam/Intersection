#pragma once
#include "decl.h"
#include <string>
#include <vector>
#include <d3d11.h>
#include "Transformable.h"
#include "IDrawable.h"
#include "ModeledObject.h"
#include "AmnModel.h"
#include "Font.h"

class RenderWindow;
class Text : public Transformable, public IDrawable
{
	friend class UIText;
public:
	typedef struct 
	{
		float stringNum;
		float x0, y0, x1, y1;
		float x_off, y_off; 
		float advance;
		float width, height;
	} TextCharacterDescription;

	DECL Text(RenderWindow* renderWindow, unsigned int const max_chars_count, VertexShader* vertexShader, PixelShader* pixelShader);
	DECL ~Text();
	DECL void setMaxCharsCount(unsigned int const max_chars_count);
	DECL void setText(std::string const text);
	DECL void setFont(Font* const font);
	DECL virtual void setScale(float3 scale) override;
	DECL void setStringsGap(const float gap);
	DECL void setTextOrigin(const float2 textOrigin);
	DECL void setFontSize(const float fontSize);
	DECL void setAttachment(const float2 attachment);

	DECL void setColor(const float4 color);
	DECL float4 getColor() const;

	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;
protected:
	RenderWindow* renderWindow;
	ModeledObject* textFrame;
	AmnModel* textFrameModel;
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	unsigned int maxCharsCount;

	unsigned int textCharsCount = 0;
	const unsigned int textDataCbuffSlot_ = 1;
	const unsigned int glyphsSvrSlot_ = 20;

	float stringsGap = 0.1f;
	float2 textOrigin = {0.02f, 0.05f};
	float2 modelScale = {1, 1};
	float2 textSize = {1, 1};
	float fontSize = 1;
	float4 color_ = {1, 1, 1, 1};
	float2 attachment = float2{};
	std::vector<Font::glyph_info> textCharacters;
	ID3D11Buffer* textCharactersBuffer;
	ID3D11ShaderResourceView* textCharactersSRV;
	Font* font;
};

