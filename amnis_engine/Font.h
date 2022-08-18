#pragma once
#include <ft2build.h>
#include "Texture.h"
#include "RenderWindow.h"
#include FT_FREETYPE_H
#include "decl.h"

class Font
{
public:
	struct glyph_info {
		float x0, y0, x1, y1;	// coords of glyph in the texture atlas
		float x_off, y_off;   // left & top bearing when rendering
		float advance;        // x advance when rendering
		float width, height;
	};
	Texture* texture;
	unsigned int numGlyphs;
	unsigned int textureWidth;
	unsigned int textureHeight;
	glyph_info* info;
	DECL Font(RenderWindow* const renderWindow, FT_Library* library, const char* path, unsigned int numGlyphs = 128);
private:
	FT_Library*  library;
	FT_Face     face;
	RenderWindow* renderWindow;
	int height = 100;
};

