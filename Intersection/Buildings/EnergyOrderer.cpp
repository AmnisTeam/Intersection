#include "EnergyOrderer.h"

EnergyOrderer::EnergyOrderer(RenderWindow* renderWindow, int posX, int posY) : Building(renderWindow, ModelsContent::tree, 1000, posX, posY, 5, 5)
{

}

void* EnergyOrderer::clone()
{
	return new EnergyOrderer(model->renderWindow, posX, posY);
}
