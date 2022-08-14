#include "pch.h"
#include "ToggleGroupe.h"

ToggleGroupe::ToggleGroupe(RenderWindow* renderWindow)
{
	this->renderWindow = renderWindow;
}

void ToggleGroupe::add(Toggle* toggle)
{
	toggles.push_back(toggle);
}

void ToggleGroupe::update()
{
	for (int i = 0; i < toggles.size(); i++)
	{
		bool state = toggles[i]->getState();
		if (activatedToggle == -1)
		{
			if (state)
				activatedToggle = i;
		}
		else
		{
			if (activatedToggle != i && state)
			{
				toggles[activatedToggle]->setState(false);
				activatedToggle = i;
				toggles[i]->setState(true);
			}

			if (toggles[activatedToggle]->getState() != true)
				toggles[activatedToggle]->setState(true);
		}
	}
}
