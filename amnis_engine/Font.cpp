#include "pch.h"
#include "Font.h"

//Font::Font(const char* path)
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
//	FT_UInt glyph_index = FT_Get_Char_Index(face, 'a');
//	error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
//	if (error)
//		throw;
//
//	if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
//		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
//}