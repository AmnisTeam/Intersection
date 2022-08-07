
cbuffer constBuffer : register(b0)
{
	float4x4 model;
	float4x4 MVP;
	float4 camPos;
};


struct Input
{
	float4 pos : POSITION;
};

struct Output
{
	float4 pos : SV_POSITION;
};
Output main(Input input)
{
	Output output;
	output.pos = mul(input.pos, MVP);
	return output;
}


//cbuffer constBuffer : register(b0)
//{
//	float4x4 model;
//	float4x4 MVP;
//	float4 camPos;
//};


//struct Input
//{
//	float4 pos : POSITION;
//	float4 texCoord : TEXCOORD;
//	float3 normal : NORMAL;
//};

//struct Output
//{
//	float4 pos : SV_POSITION;
//	float4 worldPos : POSITION;
//	float4 texCoord : TEXCOORD;
//	float3 normal : NORMAL;
//	float4 camPos : K;
//};

///*
// r r 0 0
// r r 0 0
// 0 0 0 0
// 0 0 0 0
//*/
///*
// r r r tx
// r r r ty
// r r r tz
// 0 0 0 1
//*/

//Output main(Input input)
//{
//	Output output;
//	output.worldPos = mul(input.pos, model);
//	output.pos = mul(input.pos, MVP);
//	output.texCoord = input.texCoord;
//	output.normal = mul(input.normal, (float3x3) model);
//	output.camPos = camPos;
//	return output;
//}
