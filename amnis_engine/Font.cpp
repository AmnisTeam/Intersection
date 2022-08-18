#include "pch.h"
#include "Font.h"
#define NUM_GLYPHS 128

//Font::Font(RenderWindow* const renderWindow, FT_Library* library, const char* path)
//{
//	FT_Error error = FT_Init_FreeType(&library);
//	if (error)
//		throw;
//
//	error = FT_New_Face(library, path, 0, &face);
//	if (error == FT_Err_Unknown_File_Format)
//		throw;
//	else if (error)
//		throw;
//
//	//FT_UInt glyph_index = FT_Get_Char_Index(face, x * y);
//	//error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
//	//if (error)
//	//	throw;
//
//	//if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
//	//	error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
//
//
//	struct Symbol
//	{
//		int width;
//		int height;
//		unsigned char* buffer;
//	};
//
//	struct glyph_info {
//		int x0, y0, x1, y1;	// coords of glyph in the texture atlas
//		int x_off, y_off;   // left & top bearing when rendering
//		int advance;        // x advance when rendering
//	} info[NUM_GLYPHS];
//
//	int countSymbols = (126 + 1) - ' ';
//
//	Symbol* symbol = new Symbol[countSymbols];
//
//
//
//	int width = 0;
//	int height = 0;
//
//
//
//
//	//for (int x = 0; x < countSymbols; x++)
//	//{
//	//	FT_UInt glyph_index = FT_Get_Char_Index(face, ' ' + x);
//	//	error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
//	//	if (error)
//	//		throw;
//
//	//	if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
//	//	error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
//
//	//	symbol[x].width = face->glyph->bitmap.width;
//	//	symbol[x].height = face->glyph->bitmap.rows;
//	//	symbol[x].buffer = new unsigned char[symbol[x].width * symbol[x].height];
//
//
//	//	width += face->glyph->bitmap.width;
//	//	height += face->glyph->bitmap.rows;
//
//	//	int k = face->glyph->bitmap_left;
//	//	int kk = face->glyph->bitmap_top + face->glyph->bitmap.rows;
//	//	int point = 0;
//	//}
//
//
//
//	FT_Set_Char_Size(face, 0, 26.6 * 15, 96, 96);
//	//FT_Set_Pixel_Sizes(face, 15, 15);
//
//	face->size->metrics.ascender;
//	face->ascender; // Максимальная высота от базовой линии
//	face->descender; // Максимальная высота вниз от базовой линии
//	face->max_advance_height;
//	face->max_advance_width;
//	face->glyph->bitmap.width; // Ширина глифа
//	face->glyph->bitmap.rows; // Высота глифа
//	face->glyph->bitmap_left; // Отступ свлево от точки отрисовки (которая находится слева снизу)
//	face->glyph->bitmap_top; // Отступ сверху от точки отрисовки (которая находится слева снизу)
//	face->glyph->advance; // Отступ слева от точки отрисовки до следующего символа
//
//
//
//	int max_dim = (1 + (face->size->metrics.height >> 6)) * ceilf(sqrtf(128));
//	int tex_width = 1;
//	while (tex_width < max_dim) tex_width <<= 1;
//	int tex_height = tex_width;
//
//	unsigned char* pixels = (unsigned char*)calloc(tex_width * tex_height, 1);
//	int pen_x = 0, pen_y = 0;
//
//	for (int i = 0; i < NUM_GLYPHS; ++i) {
//		FT_Load_Char(face, i, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LIGHT);
//		FT_Bitmap* bmp = &face->glyph->bitmap;
//
//		if (pen_x + bmp->width >= tex_width) {
//			pen_x = 0;
//			pen_y += ((face->size->metrics.height >> 6) + 1);
//		}
//
//		for (int row = 0; row < bmp->rows; ++row) {
//			for (int col = 0; col < bmp->width; ++col) {
//				int x = pen_x + col;
//				int y = pen_y + row;
//				pixels[y * tex_width + x] = bmp->buffer[row * bmp->pitch + col];
//			}
//		}
//
//		// this is stuff you'd need when rendering individual glyphs out of the atlas
//
//		info[i].x0 = pen_x;
//		info[i].y0 = pen_y;
//		info[i].x1 = pen_x + bmp->width;
//		info[i].y1 = pen_y + bmp->rows;
//
// 		info[i].x_off = face->glyph->bitmap_left;
//		info[i].y_off = face->glyph->bitmap_top;
//		info[i].advance = face->glyph->advance.x >> 6;
//
//		pen_x += bmp->width + 1;
//	}
//
//	//texture = new Texture(renderWindow->graphics, face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, DXGI_FORMAT_R8_UNORM, 1);
//	texture = new Texture(renderWindow->graphics, pixels, tex_width, tex_height, DXGI_FORMAT_R8_UNORM, 1);
//
//	//delete[countX * countY * widthSym * heightSym] buffer;
//}

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