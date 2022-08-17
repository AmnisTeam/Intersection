#include "ChaosFurnace.h"

ChaosFurnace::ChaosFurnace(RenderWindow* renderWindow, int posX, int posY) : Building(renderWindow, ModelsContent::sphere, 500, posX, posY, 2, 2)
{

}

void* ChaosFurnace::clone()
{
	return new ChaosFurnace(model->renderWindow, posX, posY);
}
