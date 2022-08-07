
cbuffer constBuffer : register(b0)
{
	float4x4 model;
	float4x4 MVP;
	float4 camPos;
};


struct Input
{
	float4 pos : POSITION;
	float4 texCoord : TEXCOORD;
	float4 normal : NORMAL;
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;
};

struct Output
{
	float4 pos : SV_POSITION;
	float4 worldPos : POSITION;
	float4 texCoord : TEXCOORD;
	float4 normal : NORMAL;
	float4 camPos : CAMPOS;
	float3 tangent : TANGENT;
	float3 bitangent : BITANGENT;
};

Output main(Input input)
{
	Output output;
	output.pos = mul(input.pos, MVP);
	output.worldPos = mul(input.pos, model);
	output.texCoord = input.texCoord;
	output.normal.xyz = mul(input.normal.xyz, (float3x3)model);
	output.camPos = camPos;
	output.tangent = mul(input.tangent.xyz, (float3x3) model);
	output.bitangent = mul(input.bitangent.xyz, (float3x3) model);
	return output;
}