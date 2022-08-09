#pragma once

class Graphics;
class Texture;
class RenderWindow;
class TexturesContent
{
public:
	static Texture* textureSky;
	static Texture* stoneWallNormalMap;
	static Texture* stoneWallAlbedo;
	static Texture* flatNormalMap;
	static Texture* wheelRobotBaseColor;
	static Texture* wheelRobotNormal;
	static Texture* bugAlbedo;
	static Texture* ghosthzAlbedo;

	static void load(RenderWindow* renderWindow);
};

