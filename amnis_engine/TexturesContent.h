#pragma once
#include "decl.h"

class Graphics;
class Texture;
class TexturesContent
{
public:
	Graphics* graphics;
	Texture* textureSky;
	Texture* stoneWallNormalMap;
	Texture* stoneWallAlbedo;
	Texture* flatNormalMap;
	Texture* wheelRobotBaseColor;
	Texture* wheelRobotNormal;
	Texture* bugAlbedo;
	Texture* ghosthzAlbedo;
	DECL TexturesContent(Graphics* graphics);
	DECL ~TexturesContent();
};

