#include "pch.h"
#include "DirectLightSource.h"
#include "RenderWindow.h"

DirectLightSource::DirectLightSource(RenderWindow* renderWindow, char* modelPath) : AmnModel(renderWindow, modelPath, new DefaultVertexShader(renderWindow->graphics, L"VertexShader.hlsl"), new PixelShader(renderWindow->graphics, L"PSDirectLight.hlsl"))
{

}
