#pragma once
#include "IDrawable.h"
#include "Transformable.h"
#include "decl.h"

class RenderWindow;
class ModeledObject;

class PointLight : public Transformable, public IDrawable
{
public:
	RenderWindow* renderWindow;
	ModeledObject* model;
	struct PointLightDesc
	{
		float3 position;
		float kc;
		float kl;
		float kq;
		float4 color;
		bool turnedOn;
	};
	float kc = 1;
	float kl = 0.010f;
	float kq = 0.0005f;
	float4 color = { 1, 1, 1, 1 };
	bool turnedOn = true;


	DECL PointLight(RenderWindow* renderWindow, Model* model, bool bind = true);
	DECL ~PointLight();
	DECL void bind(RenderWindow* renderWindow);
	DECL virtual void setPosition(float3 position) override;
	DECL void setColor(float4 color);
	DECL void setFactors(float3 factors);
	DECL void setParams(float3 position, float4 color, float3 factors);
	DECL void turn(bool on);
	DECL virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};

