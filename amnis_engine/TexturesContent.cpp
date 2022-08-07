#include "pch.h"
#include "TexturesContent.h"
#include "Graphics.h"
#include "Texture.h"

TexturesContent::TexturesContent(Graphics* graphics)
{
	this->graphics = graphics;
	textureSky = new Texture(graphics, L"Textures//texturify_pano-1-2.jpg");
	stoneWallNormalMap = new Texture(graphics, L"Wall_Stone_017_Normal.jpg");
	stoneWallAlbedo = new Texture(graphics, L"Wall_Stone_017_BaseColor.jpg");
	flatNormalMap = new Texture(graphics, L"Textures\\14015-normal.jpg");
	wheelRobotBaseColor = new Texture(graphics, L"Models\\wheeled-robot\\textures\\DefaultMaterial_Base_color.png");
	wheelRobotNormal = new Texture(graphics, L"Models\\wheeled-robot\\textures\\DefaultMaterial_Normal_OpenGL.png");
	bugAlbedo = new Texture(graphics, L"Textures//Graphosoma.png");
	ghosthzAlbedo = new Texture(graphics, L"Models\\ghosthz\\textures\\d9112f1021da1a04.png");
}

TexturesContent::~TexturesContent()
{
	delete textureSky;
	delete stoneWallNormalMap;
	delete stoneWallAlbedo;
	delete flatNormalMap;
	delete wheelRobotBaseColor;
	delete wheelRobotNormal;
	delete bugAlbedo;
}
