#include "pch.h"
#include "Font.h"
#define NUM_GLYPHS 128

Font::Font(RenderWindow* const renderWindow, FT_Library* library, const char* path, unsigned int numGlyphs)
{
	this->numGlyphs = numGlyphs;
	info = new glyph_info[numGlyphs];

	FT_Error error = FT_New_Face(*library, path, 0, &face);
	if (error == FT_Err_Unknown_File_Format)
		throw;
	else if (error)
		throw;



	//FT_Set_Char_Size(face, 0, 26.6 * 15, 96, 96);
	FT_Set_Pixel_Sizes(face, 0, height);

	int max_dim = (1 + (face->size->metrics.height >> 6)) * ceilf(sqrtf(numGlyphs));
	int tex_width = 1;
	while (tex_width < max_dim) tex_width <<= 1;
	int tex_height = tex_width;

	textureWidth = tex_width;
	textureHeight = tex_height;

	unsigned char* pixels = (unsigned char*)calloc(tex_width * tex_height, 1);
	int pen_x = 0, pen_y = 0;

	for (int i = 0; i < numGlyphs; ++i) {
		FT_Load_Char(face, i, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LIGHT);
		FT_Bitmap* bmp = &face->glyph->bitmap;

		if (pen_x + bmp->width >= tex_width) {
			pen_x = 0;
			pen_y += ((face->size->metrics.height >> 6) + 1);
		}

		for (int row = 0; row < bmp->rows; ++row) {
			for (int col = 0; col < bmp->width; ++col) {
				int x = pen_x + col;
				int y = pen_y + row;
				pixels[y * tex_width + x] = bmp->buffer[row * bmp->pitch + col];
			}
		}

		// this is stuff you'd need when rendering individual glyphs out of the atlas

		info[i].x0 = (float)pen_x / tex_width;
		info[i].y0 = (float)pen_y / tex_height;
		info[i].x1 = (float)pen_x / tex_width + (float)bmp->width / tex_width;
		info[i].y1 = (float)pen_y / tex_height + (float)bmp->rows / tex_height;

		info[i].width = (float)bmp->width / tex_width;
		info[i].height = (float)bmp->rows / tex_height;

		info[i].x_off = (float)face->glyph->bitmap_left / tex_width;
		info[i].y_off = (float)face->glyph->bitmap_top / tex_height;
		info[i].advance = (float)(face->glyph->advance.x >> 6) / tex_width;

		pen_x += bmp->width + 1;
	}

	texture = new Texture(renderWindow->graphics, pixels, tex_width, tex_height, DXGI_FORMAT_R8_UNORM, 1);
}