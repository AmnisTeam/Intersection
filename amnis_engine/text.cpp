#include "pch.h"
#include "text.h"

Text::Text(RenderWindow* renderWindow, std::string text, Font* font, VertexShader* vertexShader, PixelShader* pixelShader)
{
	this->renderWindow = renderWindow;

	float penX = 0, penY = 0;
	for (int g = 0; g < text.length(); g++)
	{
		unsigned int firstVertexID = g * 4;
		Font::glyph_info glyphInfo = font->info[text[g]];

		// v2 v3
		// v1 v4

		float3 v1Pos = {penX + glyphInfo.x_off, penY - (glyphInfo.height - glyphInfo.y_off), 0 };
		float3 v2Pos = {penX + glyphInfo.x_off, penY - (glyphInfo.height - glyphInfo.y_off) + glyphInfo.height, 0 };
		float3 v3Pos = {penX + glyphInfo.x_off + glyphInfo.width, penY + -(glyphInfo.height - glyphInfo.y_off) + glyphInfo.height, 0 };
		float3 v4Pos = {penX + glyphInfo.x_off + glyphInfo.width, penY + -(glyphInfo.height - glyphInfo.y_off), 0};

		float2 v1TexCoords = { (float)glyphInfo.x0, (float)glyphInfo.y1 };
		float2 v2TexCoords = { (float)glyphInfo.x0, (float)glyphInfo.y0 };
		float2 v3TexCoords = { (float)glyphInfo.x1, (float)glyphInfo.y0 };
		float2 v4TexCoords = { (float)glyphInfo.x1, (float)glyphInfo.y1 };

		vertices.push_back({ v1Pos, v1TexCoords, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });
		vertices.push_back({ v2Pos, v2TexCoords, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });
		vertices.push_back({ v3Pos, v3TexCoords, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });
		vertices.push_back({ v4Pos, v4TexCoords, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });

		indices.push_back(firstVertexID);
		indices.push_back(firstVertexID + 1);
		indices.push_back(firstVertexID + 3);

		indices.push_back(firstVertexID + 3);
		indices.push_back(firstVertexID + 1);
		indices.push_back(firstVertexID + 2);

		penX += glyphInfo.advance;
	}


	model = new AmnModel(renderWindow->graphics, vertices, indices, vertexShader, pixelShader);
	modelObject = new ModeledObject(renderWindow, model, vertexShader, pixelShader);
	setScale({50, 50});
}

void Text::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(modelObject, state);
}
