
struct glyph_info
{
	float stringNum;
	float x0, y0, x1, y1; // coords of glyph in the texture atlas
	float x_off, y_off; // left & top bearing when rendering
	float advance; // x advance when rendering
	float width, height;
};

StructuredBuffer<glyph_info> glyphs : register(t20);

cbuffer ColorData : register(b0)
{
	float4 color;
};

cbuffer TextData : register(b1)
{
	unsigned int textCharsCount;
	float stringsGap;
	float2 modelScale;
	float2 textOrigin;
	float fontSize;
	float2 attachment;
};

Texture2D texture0 : register(t0);
Texture2D textureAtlas : register(t3);
Texture2D normalMap : register(t1);
Texture2D textureSky : register(t2);

SamplerState samplerState : register(s0);

struct Input
{
	float4 pos : SV_POSITION;
	float4 worldPos : POSITION;
	float4 texCoord : TEXCOORD;
	float4 normal : NORMAL;
	float4 camPos : CAMPOS;
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;
};

bool withinArea(float2 inputPoint, float left, float top, float right, float bottom)
{
	if (inputPoint.x >= left && inputPoint.x <= right)
		if (inputPoint.y >= top && inputPoint.y <= bottom)
			return true;
	return false;
}

float4 main(Input input) : SV_TARGET
{
	float4 color = 0;
	input.texCoord.xy = float2(input.texCoord.x * modelScale.x, input.texCoord.y * modelScale.y);
	float2 attachedTextOrigin = textOrigin;
	
	float textWidth = 0, textHeight = 0;

	float maxCharsHeight = 0;
	float maxCharsOffset = 0;
	for (int g = 0; g < textCharsCount; g++)
	{
		textWidth += glyphs[g].advance * fontSize;
		maxCharsHeight = max(maxCharsHeight, glyphs[g].height);
		maxCharsOffset = max(maxCharsOffset, glyphs[g].height - glyphs[g].y_off);
		if (g > 0)
		{
			if (glyphs[g - 1].stringNum != glyphs[g].stringNum)
			{
				textHeight += stringsGap;
			}
		}
	}
	textHeight += maxCharsOffset + maxCharsHeight;

	if (attachment.x >= 0.5f)
		attachedTextOrigin.x = modelScale.x * attachment.x - attachedTextOrigin.x - textWidth * attachment.x;
	else
		attachedTextOrigin.x = attachedTextOrigin.x + modelScale.x * attachment.x - textWidth * attachment.x;
	
	if (attachment.y >= 0.5f)
		attachedTextOrigin.y = modelScale.y * attachment.y - attachedTextOrigin.y - textHeight * attachment.y;
	else
		attachedTextOrigin.y = attachedTextOrigin.y + modelScale.y * attachment.y - textHeight * attachment.y;
	
	float penX = attachedTextOrigin.x, penY = attachedTextOrigin.y;
	for (int i = 0; i < textCharsCount; i++)
	{
		if (i > 0)
			if (glyphs[i - 1].stringNum != glyphs[i].stringNum)
			{
				penX = attachedTextOrigin.x;
				penY += stringsGap;
			}
		
		float left = penX + glyphs[i].x_off * fontSize;
		float top = penY - glyphs[i].y_off * fontSize;
		float right = penX + (glyphs[i].x_off + glyphs[i].width) * fontSize;
		float bottom = penY + (glyphs[i].height - glyphs[i].y_off) * fontSize;
		
		float x0 = glyphs[i].x0;
		float y0 = glyphs[i].y0;

		if (withinArea(float2(input.texCoord.x, input.texCoord.y), left, top, right, bottom))
		{
			float2 posInGlyph = float2(x0 + (input.texCoord.x - left) / fontSize, y0 + (input.texCoord.y - top) / fontSize);
			color = float4(color.xyz, textureAtlas.Sample(samplerState, posInGlyph).r);
			//color = float4(0, 0, 0, textureAtlas.Sample(samplerState, posInGlyph).r);
			//color = float4(1, 1, 1, 1);
		}
		penX += glyphs[i].advance * fontSize;
	}
	return color;
}