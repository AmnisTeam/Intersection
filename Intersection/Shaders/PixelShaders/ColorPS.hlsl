cbuffer colorValue : register(b0)
{
	float4 constantColor;
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
	return float4(constantColor.xyz, 1);
}