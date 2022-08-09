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
	wchar_t fileName[1000];
	GetModuleFileName(NULL, fileName, 1000);
	std::wstring directory = std::wstring(fileName);
	std::wstring path = directory.substr(0, directory.find_last_of('\\')) + L"\\";

	textureSky = new Texture(renderWindow->graphics, (path + L"Textures//texturify_pano-1-2.jpg").c_str());
	stoneWallNormalMap = new Texture(renderWindow->graphics, (path + L"Textures\\Wall_Stone_017_Normal.jpg").c_str());
	stoneWallAlbedo = new Texture(renderWindow->graphics, (path + L"Textures\\Wall_Stone_017_BaseColor.jpg").c_str());
	flatNormalMap = new Texture(renderWindow->graphics, (path + L"Textures\\14015-normal.jpg").c_str());
	wheelRobotBaseColor = new Texture(renderWindow->graphics, (path + L"Models\\wheeled-robot\\textures\\DefaultMaterial_Base_color.png").c_str());
	wheelRobotNormal = new Texture(renderWindow->graphics, (path + L"Models\\wheeled-robot\\textures\\DefaultMaterial_Normal_OpenGL.png").c_str());
	bugAlbedo = new Texture(renderWindow->graphics, (path + L"Textures//Graphosoma.png").c_str());
	ghosthzAlbedo = new Texture(renderWindow->graphics, (path + L"Models\\ghosthz\\textures\\d9112f1021da1a04.png").c_str());
}
