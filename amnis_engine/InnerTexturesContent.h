#pragma once
#include "decl.h"
class Graphics;
class Texture;
class RenderWindow;

class InnerTexturesContent
{
public:
	static Texture* pureWhite;
	DECL static void load(RenderWindow* renderWindow);
};