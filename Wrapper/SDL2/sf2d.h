/*

The MIT License (MIT)

Copyright (c) 2016 Gameblabla

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

*/

#ifndef SF2D_DEFINE
#define SF2D_DEFINE

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define u8 unsigned char
#define u32 unsigned long
#define u64 unsigned long long
#ifndef bool
#define bool u8
#endif
#define true 1
#define false 0

#define GFX_TOP 1
#define GFX_BOTTOM 0 
#define GFX_LEFT 0
#define GFX_RIGHT 0
#define SF2D_PLACE_RAM 0

#define sf2d_texture SDL_Texture
#define sftd_font TTF_Font
#define gfxScreen_t int

#define sf2d_pool_malloc malloc
#define sf2d_pool_memalign memalign
#define sf2d_pool_calloc calloc

#define RGBA8(r, g, b, a)  ((((a)&0xFF)<<24) | (((b)&0xFF)<<16) | (((g)&0xFF)<<8) | (((r)&0xFF)<<0))
#define RGBA8_GET_R(c)   (((c) >> 0) & 0xFF)
#define RGBA8_GET_G(c)   (((c) >> 8) & 0xFF)
#define RGBA8_GET_B(c)   (((c) >> 16) & 0xFF)
#define RGBA8_GET_A(c)   (((c) >> 24) & 0xFF)
#define SF2D_GPUCMD_DEFAULT_SIZE   0x80000
#define SF2D_TEMPPOOL_DEFAULT_SIZE   0x80000
#define SF2D_DEFAULT_DEPTH   0.5f

typedef enum {
	TEXFMT_RGBA8  =  0,
	TEXFMT_RGB8   =  1,
	TEXFMT_RGB5A1 =  2,
	TEXFMT_RGB565 =  3,
	TEXFMT_RGBA4  =  4,
	TEXFMT_IA8    =  5,

	TEXFMT_I8     =  7,
	TEXFMT_A8     =  8,
	TEXFMT_IA4    =  9,
	TEXFMT_I4     = 10,
	TEXFMT_A4     = 11,
	TEXFMT_ETC1   = 12,
	TEXFMT_ETC1A4 = 13
} sf2d_texfmt;

int sf2d_init();
int sf2d_init_advanced(int gpucmd_size, int temppool_size);
int sf2d_fini();

void sf2d_set_3D(u8 enable);

void sf2d_set_clear_color(u32 color);
void sf2d_set_vblank_wait(int enable);
void sf2d_start_frame(int screentodraw, int wheretodraw);
void sf2d_end_frame();

sf2d_texture* sfil_load_PNG_file(const char* path, int somebullshitwedontcarefor);
sf2d_texture *sf2d_create_texture_mem_RGBA8(unsigned char *src_buffer, int src_w, int src_h, int pixelformat, int shitnotimplemented);

void sf2d_draw_texture(sf2d_texture *yourmom, int x, int y);
void sf2d_draw_texture_rotate(sf2d_texture *texture, int x, int y, float rad);
void sf2d_draw_texture_scale(sf2d_texture *texture, int x, int y, float x_scale, float y_scale);
void sf2d_draw_texture_part(sf2d_texture *texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h);
void sf2d_draw_texture_part_scale(sf2d_texture *texture, float x, float y, float tex_x, float tex_y, float tex_w, float tex_h, float x_scale, float y_scale);
void sf2d_draw_texture_part_rotate_scale(sf2d_texture *texture, int x, int y, float rad, int tex_x, int tex_y, int tex_w, int tex_h, float x_scale, float y_scale);
void sf2d_draw_texture_part_scale_blend(sf2d_texture *texture, float x, float y, float tex_x, float tex_y, float tex_w, float tex_h, float x_scale, float y_scale, u32 color);
void sf2d_draw_texture_rotate_cut_scale(sf2d_texture *texture, int x, int y, float rad, int tex_x, int tex_y, int tex_w, int tex_h, float x_scale, float y_scale);
void sf2d_draw_texture_blend(sf2d_texture *texture, int x, int y, u32 color);
void sf2d_draw_texture_part_blend(sf2d_texture *texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h, u32 color);
void sf2d_draw_texture_depth (sf2d_texture *texture, int x, int y, signed short z);

void sf2d_set_pixel (sf2d_texture *texture, int x, int y, u32 new_color);
u32 sf2d_get_pixel(sf2d_texture *texture, int x, int y);
void sf2d_texture_tile32(sf2d_texture *texture);
void sf2d_free_texture(sf2d_texture *texture);
void sf2d_swapbuffers();

gfxScreen_t sf2d_get_current_screen();
gfxScreen_t sf2d_get_current_side();

void sf2d_draw_line(int x0, int y0, int x1, int y1, u32 color);
void sf2d_draw_rectangle(int x, int y, int w, int h, u32 color);
void sf2d_draw_triangle(float x1, float y1, float x2, float y2, float x3, float y3, u32 color);
void sf2d_draw_fill_circle(int rad, int x, int y, u32 color);
void sf2d_set_pixel (sf2d_texture *texture, int x, int y, u32 new_color);

unsigned int sf2d_pool_space_free();
void sf2d_pool_reset();

float sf2d_get_fps();

/*
 * sftd functions for text drawing 
*/

void sftd_init();
void sftd_fini();
sftd_font* sftd_load_font_file(const char* path);
void sftd_free_font(sftd_font* ex);
void sftd_draw_textf(sftd_font *font, int x, int y, u32 color, int size, const char* string_text);

#endif
