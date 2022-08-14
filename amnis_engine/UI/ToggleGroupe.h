#pragma once
#include "ToggleGroupe.h"
#include "Toggle.h"
#include <vector>
#include "../decl.h"

class ToggleGroupe
{
public:
	DECL ToggleGroupe(RenderWindow* renderWindow);
	DECL void add(Toggle* toggle);
	DECL void update();
private:
	RenderWindow* renderWindow;
	std::vector<Toggle*> toggles;
	int activatedToggle = 1;
};

