#include "pch.h"
#include "ModelsContent.h"
#include "RenderWindow.h"

ModelsContent::ModelsContent(RenderWindow* renderWindow)
{
	sphere = new Model(renderWindow->graphics, (char*)"Models//sphere.obj", renderWindow->graphics->shadersContent->defaultVS, renderWindow->graphics->shadersContent->defaultPS);
	plane = new Model(renderWindow->graphics, (char*)"Models//Plane.obj", renderWindow->graphics->shadersContent->defaultVS, renderWindow->graphics->shadersContent->defaultPS);
	tree = new Model(renderWindow->graphics, (char*)"Models\\Tree\\source\\tree2.fbx", renderWindow->graphics->shadersContent->defaultVS, renderWindow->graphics->shadersContent->defaultPS);
	ghosthz = new Model(renderWindow->graphics, (char*)"Models\\ghosthz\\source\\ghosthz.fbx", renderWindow->graphics->shadersContent->defaultVS, renderWindow->graphics->shadersContent->defaultPS);
}

ModelsContent::~ModelsContent()
{
	delete sphere;
	delete plane;
}
