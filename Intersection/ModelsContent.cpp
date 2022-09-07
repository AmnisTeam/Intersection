#include "ModelsContent.h"
#include "RenderWindow.h"
#include "AmnModel.h"
#include "ShadersContent.h"

AmnModel* ModelsContent::sphere;
AmnModel* ModelsContent::plane;
AmnModel* ModelsContent::tree;
AmnModel* ModelsContent::ghosthz;
AmnModel* ModelsContent::box;
AmnModel* ModelsContent::dragon;
AmnModel* ModelsContent::wolf;
AmnModel* ModelsContent::knight;
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

	sphere = new AmnModel(renderWindow, (char*)(str + "Models\\sphere.obj").c_str(), renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);
	plane = new AmnModel(renderWindow, (char*)(str + "Models\\Plane.obj").c_str(), renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);
	tree = new AmnModel(renderWindow, (char*)(str + "Models\\Tree\\source\\tree2.fbx").c_str(), renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);
	tree->setScale({1 / 100.0, 1 / 100.0 , 1 / 100.0 });
	
	ghosthz = new AmnModel(renderWindow, (char*)(str + "Models\\ghosthz\\source\\ghosthz.fbx").c_str(), renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);
	ghosthz->setScale({ 1 / 100.0, 1 / 100.0 , 1 / 100.0 });

	dragon = new AmnModel(renderWindow, (char*)(str + "Models\\dragon\\fbx\\Dragon 2.5_fbx.fbx").c_str(), renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);
	wolf = new AmnModel(renderWindow, (char*)(str + "Models\\Wolf\\Wolf.fbx").c_str(), renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);
	knight = new AmnModel(renderWindow, (char*)(str + "Models\\Knight\\source\\ggfggf.fbx").c_str(), renderWindow->graphics->defaultVS, renderWindow->graphics->defaultPS);

	std::vector<Vertex> boxVertices;

	//Задняя грань
	boxVertices.push_back({ 0, 1, 0,      0, 0,    0, 0, -1 });
	boxVertices.push_back({ 1, 1, 0,      1, 0,    0, 0, -1 });
	boxVertices.push_back({ 1, 0, 0,      1, 1,    0, 0, -1 });
	boxVertices.push_back({ 0, 0, 0,      0, 1,    0, 0, -1 });

	boxVertices.push_back({ 1, 1, 0,      0, 0,    1, 0, 0 });
	boxVertices.push_back({ 1, 1, 1,      1, 0,    1, 0, 0 });
	boxVertices.push_back({ 1, 0, 1,      1, 1,    1, 0, 0 });
	boxVertices.push_back({ 1, 0, 0,      0, 1,    1, 0, 0 });


	boxVertices.push_back({ 0, 1, 1,      0, 0,    0, 0, 1 });
	boxVertices.push_back({ 1, 1, 1,      1, 0,    0, 0, 1 });
	boxVertices.push_back({ 1, 0, 1,      1, 1,    0, 0, 1 });
	boxVertices.push_back({ 0, 0, 1,      0, 1,    0, 0, 1 });


	boxVertices.push_back({ 0, 1, 0,      0, 0,    -1, 0, 0 });
	boxVertices.push_back({ 0, 1, 1,      1, 0,    -1, 0, 0 });
	boxVertices.push_back({ 0, 0, 1,      1, 1,    -1, 0, 0 });
	boxVertices.push_back({ 0, 0, 0,      0, 1,    -1, 0, 0 });


	boxVertices.push_back({ 0, 1, 1,      0, 0,    0, 1, 0 });
	boxVertices.push_back({ 1, 1, 1,      1, 0,    0, 1, 0 });
	boxVertices.push_back({ 1, 1, 0,      1, 1,    0, 1, 0 });
	boxVertices.push_back({ 0, 1, 0,      0, 1,    0, 1, 0 });



	boxVertices.push_back({ 0, 0, 1,      0, 0,    0, -1, 0 });
	boxVertices.push_back({ 1, 0, 1,      1, 0,    0, -1, 0 });
	boxVertices.push_back({ 1, 0, 0,      1, 1,    0, -1, 0 });
	boxVertices.push_back({ 0, 0, 0,      0, 1,    0, -1, 0 });



	std::vector<int> boxIndices;
	boxIndices.push_back(0);
	boxIndices.push_back(1);
	boxIndices.push_back(2);

	boxIndices.push_back(2);
	boxIndices.push_back(3);
	boxIndices.push_back(0);



	boxIndices.push_back(4);
	boxIndices.push_back(5);
	boxIndices.push_back(6);

	boxIndices.push_back(6);
	boxIndices.push_back(7);
	boxIndices.push_back(4);



	boxIndices.push_back(10);
	boxIndices.push_back(9);
	boxIndices.push_back(8);

	boxIndices.push_back(8);
	boxIndices.push_back(11);
	boxIndices.push_back(10);


	boxIndices.push_back(14);
	boxIndices.push_back(13);
	boxIndices.push_back(12);

	boxIndices.push_back(12);
	boxIndices.push_back(15);
	boxIndices.push_back(14);



	boxIndices.push_back(16);
	boxIndices.push_back(17);
	boxIndices.push_back(18);

	boxIndices.push_back(18);
	boxIndices.push_back(19);
	boxIndices.push_back(16);


	boxIndices.push_back(21);
	boxIndices.push_back(20);
	boxIndices.push_back(22);

	boxIndices.push_back(22);
	boxIndices.push_back(20);
	boxIndices.push_back(23);

	box = new AmnModel(renderWindow, boxVertices, boxIndices, ShadersContent::defaultVS, ShadersContent::defaultPS);
}
