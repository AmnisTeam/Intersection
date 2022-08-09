#include "TexturesContent.h"
#include "RenderWindow.h"
#include "Texture.h"

Texture* TexturesContent::textureSky;
Texture* TexturesContent::stoneWallNormalMap;
Texture* TexturesContent::stoneWallAlbedo;
Texture* TexturesContent::flatNormalMap;
Texture* TexturesContent::wheelRobotBaseColor;
Texture* TexturesContent::wheelRobotNormal;
Texture* TexturesContent::bugAlbedo;
Texture* TexturesContent::ghosthzAlbedo;

void TexturesContent::load(RenderWindow* renderWindow)
{
	textureSky = new Texture(renderWindow->graphics, L"Textures//texturify_pano-1-2.jpg");
	stoneWallNormalMap = new Texture(renderWindow->graphics, L"Textures\\Wall_Stone_017_Normal.jpg");
	stoneWallAlbedo = new Texture(renderWindow->graphics, L"Textures\\Wall_Stone_017_BaseColor.jpg");
	flatNormalMap = new Texture(renderWindow->graphics, L"Textures\\14015-normal.jpg");
	wheelRobotBaseColor = new Texture(renderWindow->graphics, L"Models\\wheeled-robot\\textures\\DefaultMaterial_Base_color.png");
	wheelRobotNormal = new Texture(renderWindow->graphics, L"Models\\wheeled-robot\\textures\\DefaultMaterial_Normal_OpenGL.png");
	bugAlbedo = new Texture(renderWindow->graphics, L"Textures//Graphosoma.png");
	ghosthzAlbedo = new Texture(renderWindow->graphics, L"Models\\ghosthz\\textures\\d9112f1021da1a04.png");
}
