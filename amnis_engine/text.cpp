#include "pch.h"
#include "text.h"
#include "RenderWindow.h"

Text::Text(RenderWindow* renderWindow, unsigned int const max_chars_count, VertexShader* vertexShader, PixelShader* pixelShader)
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

	textFrameModel = new AmnModel(renderWindow, vertices, indices, vertexShader, pixelShader);
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

	textFrame->constantBuffersSystem->PSAddValue(textDataCbuffSlot_, &textCharsCount, "TextCharsCount", sizeof(float));
	textFrame->constantBuffersSystem->PSAddValue(textDataCbuffSlot_, &stringsGap, "StringsGap", sizeof(float));
	textFrame->constantBuffersSystem->PSAddValue(textDataCbuffSlot_, &modelScale, "ModelScale", sizeof(float2));
	textFrame->constantBuffersSystem->PSAddValue(textDataCbuffSlot_, &textOrigin, "TextOrigin", sizeof(float2));
	textFrame->constantBuffersSystem->PSAddValue(textDataCbuffSlot_, &fontSize, "FontSize", sizeof(float2));
	textFrame->constantBuffersSystem->PSAddValue(textDataCbuffSlot_, &color_, "Color", sizeof(color_));
	textFrame->constantBuffersSystem->PSAddValue(textDataCbuffSlot_, &attachment, "Attachment", sizeof(float4));
	textFrame->constantBuffersSystem->PSInit(textDataCbuffSlot_);
}

Text::~Text()
{
	textCharactersBuffer->Release();
	textCharactersSRV->Release();
}

void Text::setMaxCharsCount(unsigned int const max_chars_count)
{
	maxCharsCount = max_chars_count;
}

void Text::setText(std::string const text)
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
	textFrame->constantBuffersSystem->PSUpdateValue(textDataCbuffSlot_, "TextCharsCount", &textCharsCount);
}

void Text::setFont(Font* const font)
{
	this->font = font;
}

void Text::setScale(float3 scale)
{
	modelScale = { scale.x, scale.y };
	textFrame->constantBuffersSystem->PSUpdateValue(textDataCbuffSlot_, "ModelScale", &modelScale);
	Transformable::setScale(scale);
}

void Text::setStringsGap(const float gap)
{
	stringsGap = gap;
	textFrame->constantBuffersSystem->PSUpdateValue(textDataCbuffSlot_, "StringsGap", &stringsGap);
}

void Text::setTextOrigin(const float2 textOrigin)
{
	this->textOrigin = textOrigin;
	textFrame->constantBuffersSystem->PSUpdateValue(textDataCbuffSlot_, "TextOrigin", &this->textOrigin);
}

void Text::setFontSize(const float fontSize)
{
	this->fontSize = fontSize;
	textFrame->constantBuffersSystem->PSUpdateValue(textDataCbuffSlot_, "FontSize", &this->fontSize);
}

void Text::setAttachment(const float2 attachment)
{
	this->attachment = attachment;
	textFrame->constantBuffersSystem->PSUpdateValue(textDataCbuffSlot_, "Attachment", &this->attachment);
}

void Text::setColor(const float4 color)
{
	color_ = color;
	textFrame->constantBuffersSystem->PSUpdateValue(textDataCbuffSlot_, "Color", &color_);
}

float4 Text::getColor() const
{
	return color_;
}

void Text::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = state.modelMatrix * modelMatrix;
	renderWindow->graphics->deviceCon->PSSetShaderResources(glyphsSvrSlot_, 1, &textCharactersSRV);
	textFrame->setTexture(font->texture, 3);
	renderTarget->draw(textFrame, state);
}
