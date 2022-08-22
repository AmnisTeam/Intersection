#include "pch.h"
#include "text2.h"
#include "RenderWindow.h"

Text2::Text2(RenderWindow* renderWindow, unsigned int const max_chars_count, VertexShader* vertexShader, PixelShader* pixelShader)
{
	this->renderWindow = renderWindow;
	setMaxCharsCount(max_chars_count);


	vertices.push_back({ { -1, -1, 0 }, { 0, 1 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });
	vertices.push_back({ { -1, 1, 0 }, { 0, 0 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });
	vertices.push_back({ { 1, 1, 0 }, { 1, 0 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });
	vertices.push_back({ { 1, -1, 0 }, { 1, 1 }, {0, 0, -1}, {0, 0, 0}, {0, 0, 0} });

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);

	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(2);

	textFrameModel = new AmnModel(renderWindow->graphics, vertices, indices, vertexShader, pixelShader);
	textFrame = new ModeledObject(renderWindow, textFrameModel, vertexShader, pixelShader);


	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(TextCharacterDescription) * max_chars_count;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bufferDesc.StructureByteStride = sizeof(TextCharacterDescription);

	HRESULT hr = renderWindow->graphics->device->CreateBuffer(&bufferDesc, NULL, &textCharactersBuffer);
	if (FAILED(hr)) throw;


	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.NumElements = maxCharsCount;

	hr = renderWindow->graphics->device->CreateShaderResourceView(textCharactersBuffer, &srvDesc, &textCharactersSRV);
	if (FAILED(hr)) throw;

	textFrame->PSConstBufAdd(1);
	textFrame->PSConstBufAddValue(1, &textCharsCount, "TextCharsCount", sizeof(float));
	textFrame->PSConstBufAddValue(1, &stringsGap, "StringsGap", sizeof(float));
	textFrame->PSConstBufAddValue(1, &modelScale, "ModelScale", sizeof(float2));
	textFrame->PSConstBufAddValue(1, &textOrigin, "TextOrigin", sizeof(float2));
	textFrame->PSConstBufAddValue(1, &fontSize, "FontSize", sizeof(float2));
	textFrame->PSConstBufAddValue(1, &attachment, "Attachment", sizeof(float4));
	textFrame->PSConstBufInit(1);
}

Text2::~Text2()
{
	textCharactersBuffer->Release();
	textCharactersSRV->Release();
}

void Text2::setMaxCharsCount(unsigned int const max_chars_count)
{
	maxCharsCount = max_chars_count;
}

void Text2::setText(std::string const text)
{
	const unsigned int glyphsCount = text.size();
	textCharsCount = text.size();

	D3D11_MAPPED_SUBRESOURCE mappedSubRes{};
	HRESULT hr = renderWindow->graphics->deviceCon->Map(textCharactersBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubRes);
	if (FAILED(hr)) throw;

	textSize = {};

	char* last = (char*)mappedSubRes.pData;
	unsigned int stringNum = 0;
	for (int i = 0; i < glyphsCount; i++)
	{
		if (text[i] == '\n')
		{
			stringNum += 1;
			textCharsCount -= 1;
		}
		else
		{
			if (i == 23)
				int k = 0;

			TextCharacterDescription glyphsInfo{};
			glyphsInfo.x0 = font->info[text[i]].x0;
			glyphsInfo.y0 = font->info[text[i]].y0;
			glyphsInfo.x1 = font->info[text[i]].x1;
			glyphsInfo.y1 = font->info[text[i]].y1;

			glyphsInfo.x_off = font->info[text[i]].x_off;
			glyphsInfo.y_off = font->info[text[i]].y_off;

			glyphsInfo.advance = font->info[text[i]].advance;

			glyphsInfo.width = font->info[text[i]].width;
			glyphsInfo.height = font->info[text[i]].height;

			glyphsInfo.stringNum = stringNum;



			//textSize.x += glyphsInfo.advance * fontScale;
			//if (i > 0)
			//	if (text[i - 1].stringNum != glyphsInfo.stringNum)
			//		textHeight += stringsGap;

			memcpy(last, &glyphsInfo, sizeof(TextCharacterDescription));
			last += sizeof(TextCharacterDescription);
		}
	}
	renderWindow->graphics->deviceCon->Unmap(textCharactersBuffer, NULL);
	textFrame->PSConstBufUpdateValue(1, 0, &textCharsCount);
}

void Text2::setFont(Font* const font)
{
	this->font = font;
}

void Text2::setScale(float3 scale)
{
	modelScale = { scale.x, scale.y };
	textFrame->PSConstBufUpdateValue(1, 2, &modelScale);
	Transformable::setScale(scale);
}

void Text2::setStringsGap(const float gap)
{
	stringsGap = gap;
	textFrame->PSConstBufUpdateValue(1, 1, &stringsGap);
}

void Text2::setTextOrigin(const float2 textOrigin)
{
	this->textOrigin = textOrigin;
	textFrame->PSConstBufUpdateValue(1, 3, &this->textOrigin);
}

void Text2::setFontSize(const float fontSize)
{
	this->fontSize = fontSize;
	textFrame->PSConstBufUpdateValue(1, 4, &this->fontSize);
}

void Text2::setAttachment(const float2 attachment)
{
	this->attachment = attachment;
	textFrame->PSConstBufUpdateValue(1, 5, &this->attachment);
}

void Text2::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = state.modelMatrix * modelMatrix;
	renderWindow->graphics->deviceCon->PSSetShaderResources(20, 1, &textCharactersSRV);
	textFrame->setTexture(font->texture, 3);
	renderTarget->draw(textFrame, state);
}
