
struct PointLight
{
	float3 position;
	float kc;
	float kl;
	float kq;
	float4 color;
	bool turnedOn;
};

StructuredBuffer<PointLight> pointLights : register(t9);

cbuffer lightsCount : register(b9)
{
	unsigned int pointLightsCount;
};

cbuffer sdfsdf : register(b11)
{
	float4 color;
};

cbuffer constPbr : register(b12)
{
	float roughness;
	float metallic;
}

Texture2D texture0 : register(t0);
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

//float rand(unsigned int k, int seed)
//{
//	k = ((k + 3435 + seed) * 36245) % 10000;
//	return k / 10000.0f;
//}

float rand(float _Seed, float2 _Pixel)
{
	float result = frac(sin((_Seed + 4643) / 100.0f * dot(_Pixel, float2(12.9898f, 78.233f))) * 234622.5453f);
	_Seed += 1.0f;
	return result;
}

float4 getSkyColorPathTraced(Input input, float3 normal, float t, unsigned int valueForRand)
{
	float3 I = normalize(input.worldPos.xyz - input.camPos.xyz);
	float3 specularR = reflect(I, normal);
	float3 randHemisphere = normalize(float3(rand(valueForRand, input.camPos.xy + 20) * 2 - 1, rand(valueForRand, input.camPos.xz + 30), rand(valueForRand, input.camPos.yx + 40) * 2 - 1));

	float3 tangent = normalize(cross(normal, -normal));
	float3 bitangent = normalize(cross(normal, tangent));

	//float3 bitangent = normalize(cross(input.normal.xyz, input.tangent.xyz));
	//float3 randR = randHemisphere.x * bitangent.xyz + randHemisphere.z * input.tangent.xyz + randHemisphere.y * input.normal.xyz;
	float3 randR = randHemisphere.x * bitangent.xyz + randHemisphere.z * tangent.xyz + randHemisphere.y * normal.xyz;

	float3 R = normalize(specularR + (randR - specularR) * t);

	float3 P = normalize(float3(R.x, 0, R.z));
	float3 Ox = float3(1, 0, 0);

	float theta = (P.z >= 0 ? acos(dot(P, Ox)) : 3.14 - acos(dot(P, Ox)) + 3.14) / (2 * 3.14f);
	float phi = 1 - (R.y + 1) / 2.0f;

	float coof = 0.7;

	return max(dot(specularR, normal), 0) * textureSky.Sample(samplerState, float2(theta, phi)) * (1 - coof) + textureSky.Sample(samplerState, float2(theta, phi)) * coof;
}

float4 getSkyColor(Input input, float3 normal)
{
	float3 I = normalize(input.worldPos.xyz - input.camPos.xyz);
	float3 specularR = reflect(I, normal);

	float3 R = specularR;

	float3 P = normalize(float3(R.x, 0, R.z));
	float3 Ox = float3(1, 0, 0);

	float theta = (P.z >= 0 ? acos(dot(P, Ox)) : 3.14 - acos(dot(P, Ox)) + 3.14) / (2 * 3.14f);
	float phi = 1 - (R.y + 1) / 2.0f;

	return textureSky.Sample(samplerState, float2(theta, phi));
}


float3 myReflect(float3 i, float3 n)
{
	return i - n * dot(i, n);
}


//const float PI = 3.14; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

float DistributionGGX(float3 N, float3 H, float roughness)
{
	const float PI = 3.14159265359;
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH * NdotH;
	
	float num = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;
	
	return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r * r) / 8.0;

	float num = NdotV;
	float denom = NdotV * (1.0 - k) + k;
	
	return num / denom;
}

float GeometrySmith(float3 N, float3 V, float3 L, float roughness)
{
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);
	
	return ggx1 * ggx2;
}

float3 fresnelSchlick(float cosTheta, float3 F0)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}


float4 main(Input input) : SV_TARGET
{
	const float PI = 3.14;
	
	//float metallic = 0;
	//float roughness = 0.3f;

	
	float3 lightDirection = normalize(float3(0.5f, 1.0f, -0.2f));
	float4 lightColor = float4(1, 1, 1, 1);
	float3 viewDir = normalize(input.camPos.xyz - input.worldPos.xyz);
	float4 specularColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

	float3 normalMapColor = normalMap.Sample(samplerState, input.texCoord.xy) * 2.0f - 1.0f;
	float3 normal = normalize(normalMapColor.x * normalize(input.bitangent.xyz) + normalMapColor.y * normalize(input.tangent.xyz) + normalMapColor.z * normalize(input.normal.xyz));
	//float3 normal = input.normal.xyz;

	//float4 albedo = texture0.Sample(samplerState, input.texCoord.xy);
	float4 albedo = float4(0, 0, 1, 1);
	//float4 texColor = float4(1, 1, 1, 1);
	float4 specular = pow(max(dot(reflect(lightDirection.xyz, normal.xyz), viewDir), 0), 32) * specularColor;
	//float4 specular = 0;

	//float4 ambient = 0;
	//float4 ambient = float4(0.4f, 0.6f, 1.0f, 1.0f) * 0.4f;
	//float4 ambient = float4(0.8f, 0.8f, 1, 1.0f) * 0.8f;

	//float4 ambient = float4(0.4f, 0.6f, 1.0f, 1.0f) * 0.4f;
	//float4 ambient = 0;
	//float4 diffusion = max(dot(normal.xyz, lightDirection.xyz), 0);
	float4 diffusion = 0;
	
	//float4 aura = dot(normal.xyz, viewDir) * float4(0, 0, 1, 1);
	
	
	
	
	
	float4 aura = pow(1 - max(dot(normal.xyz, normalize(input.camPos.xyz - input.worldPos.xyz)), 0), 4) * float4(0.8, 0.8, 1, 1);

	
	float4 Lo = float4(0, 0, 0, 1);
	
	//if (pow(1 - max(dot(normal.xyz, normalize(input.camPos.xyz - input.worldPos.xyz)), 0), 3.5) > 0.3)
	//	aura = float4(0, 0, 1, 1);
	
	float4 F0 = 0.04;
	//F0 = F0 + (albedo - F0) * metallic;
	F0 = lerp(F0, albedo, metallic);
	
	for (int i = 0; i < pointLightsCount; i++)
	{
		if (pointLights[i].turnedOn)
		{
			float3 direction = pointLights[i].position - input.worldPos.xyz;
			float3 pointLightDir = normalize(direction);
			float distance = length(direction);

			float k = 1.0 / (pointLights[i].kc + pointLights[i].kl * distance + pointLights[i].kq * pointLights[i].kq * distance);
			//float4 radiance = pointLights[i].color * k;
			float4 radiance = pointLights[i].color * k;
			
			float3 H = normalize(viewDir + pointLightDir);
			
			float NDF = DistributionGGX(normal, H, roughness);
			float G = GeometrySmith(normal, viewDir, pointLightDir, roughness);
			float3 F = fresnelSchlick(max(dot(H, pointLightDir), 0.0), F0.xyz);
			
			float4 kS = float4(F, 1);
			float4 kD = 1.0 - kS;
			kD *= (1.0 - metallic);
			
			float3 numerator = NDF * G * F;
			float denominator = 4.0 * max(dot(normal, viewDir), 0) * max(dot(normal, pointLightDir), 0);
			specular = float4(numerator / max(denominator, 0.001), 1);
			
			
			//specular = pow(max(dot(reflect(pointLightDir.xyz, normal.xyz), viewDir), 0), 32) * radiance * texColor;
			
			float NdotL = max(dot(pointLightDir.xyz, normal.xyz), 0);
			
			diffusion = albedo / PI;
			//diffusion = 0;
			
			Lo += (kD * diffusion + specular) * radiance * NdotL;
		}
	}
	
	float4 ambient = 0.03 * albedo;
	float4 color = Lo + ambient;
	
	color = color / (color + 1.0);
	color = pow(color, 1.0 / 2.2);

	//return float4((diffusion.xyz * texColor.xyz + specular.xyz * texColor.xyz + ambient.xyz * texColor.xyz), 1); // For tranparency to work
	return float4(color.xyz, 1); // For tranparency to work
}