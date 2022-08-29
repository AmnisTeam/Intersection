
cbuffer buffer : register(b0)
{
	float4 overLayColor;
	float4 shadeColor;
	float shade;
	float overlay;
	float4 textureRect;
};

Texture2D texture0 : register(t0);
Texture2D normalMap : register(t1);

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

float4 main(Input input) : SV_TARGET
{	
	float rectWidth = textureRect.z - textureRect.x;
	float rectHeight = textureRect.y - textureRect.w;
	
	float2 newTexCoords = float2(textureRect.x + input.texCoord.x * rectWidth, textureRect.y + input.texCoord.y * rectHeight);
	float3 textureColor = texture0.Sample(samplerState, newTexCoords);
	
	float4 shadeColorResult = float4(textureColor.xyz, 1) * lerp(1, shadeColor, shade);
	return float4(lerp(shadeColorResult.xyz, overLayColor.xyz, overlay), 1);
}