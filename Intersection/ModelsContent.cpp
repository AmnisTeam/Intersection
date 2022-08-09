#include "ModelsContent.h"
#include "RenderWindow.h"
#include "AmnModel.h"

AmnModel* ModelsContent::sphere;
AmnModel* ModelsContent::plane;
AmnModel* ModelsContent::tree;
AmnModel* ModelsContent::ghosthz;
RenderWindow* ModelsContent::renderWindow;

void ModelsContent::load(RenderWindow* renderWindow)
{
	//wchar_t fileName[1000];
	//GetModuleFileName(NULL, fileName, 1000);
	//std::wstring directory = std::wstring(fileName);
	//std::wstring path = directory.substr(0, directory.find_last_of('\\')) + L"\\";
	//std::string str = std::string(path.size(), 0);

	//WideCharToMultiByte(0, 0, path.c_str(), path.size(), &str[0], path.size(), NULL, NULL);
	std::string str;

	sphere = new AmnModel(renderWindow->graphics, (char*)(str + "Models\\sphere.obj").c_str(), renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);
	plane = new AmnModel(renderWindow->graphics, (char*)(str + "Models\\Plane.obj").c_str(), renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);
	tree = new AmnModel(renderWindow->graphics, (char*)(str + "Models\\Tree\\source\\tree2.fbx").c_str(), renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);
	ghosthz = new AmnModel(renderWindow->graphics, (char*)(str + "Models\\ghosthz\\source\\ghosthz.fbx").c_str(), renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);
}
