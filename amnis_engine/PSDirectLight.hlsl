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


float3 myReflect(float3 i, float3 n)
{
	return i - n * dot(i, n);
}

float4 main(Input input) : SV_TARGET
{
	float3 lightDirection = normalize(float3(0, 1, 0));
	float4 lightColor = float4(1, 1, 1, 1);
	float3 viewDir = normalize(input.worldPos.xyz - input.camPos.xyz);
	float4 specularColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

	float3 normalMapColor = normalMap.Sample(samplerState, input.texCoord.xy) * 2.0f - 1.0f;
	//float3 normal = normalize(normalMapColor.x * normalize(input.bitangent.xyz) + normalMapColor.y * normalize(input.tangent.xyz) + normalMapColor.z * normalize(input.normal.xyz));
	float3 normal = input.normal.xyz;

	float4 texColor = texture0.Sample(samplerState, input.texCoord.xy);
	float4 specular = pow(max(dot(reflect(lightDirection.xyz, normal.xyz), viewDir), 0), 32) * specularColor;
	float4 ambient = float4(0.4f, 0.6f, 1.0f, 1.0f) * 0.4f;
	float4 diffusion = max(dot(normal.xyz, lightDirection.xyz), 0);

	return float4(1, 1, 1, 1);
}