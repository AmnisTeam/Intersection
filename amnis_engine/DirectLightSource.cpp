#include "pch.h"
#include "DirectLightSource.h"

DirectLightSource::DirectLightSource(Graphics* graphics, char* modelPath) : AmnModel(graphics, modelPath, new DefaultVertexShader(graphics, L"VertexShader.hlsl"), new PixelShader(graphics, L"PSDirectLight.hlsl"))
{

}
