/*

The MIT License (MIT)

Copyright (c) 2016 Gameblabla

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

*/

#include "sf2d.h"

static SDL_Window* screen;
static SDL_Renderer* renderer;
static SDL_Texture *top_screen, *bottom_screen;

static u8 result;
static u8 donotdraw = 0;
static u8 synchro = 1;
static u8 currentscreen = GFX_TOP;

u8 fontsize;

int sf2d_init()
{
	SDL_Init( SDL_INIT_VIDEO );
	screen = SDL_CreateWindow("Monkey fuck", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 480, 0);  
	
	/* Create renderer, its resolution, set to HARDWARE aceleration and Vsync turned on */
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, 400, 480);
	
	/* Clear everything on screen */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	/* Hide the mouse and grab it */
	SDL_SetRelativeMouseMode(SDL_FALSE);
	
	top_screen = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 400, 240 );
	bottom_screen = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 320, 240 );
	
	SDL_SetRenderTarget( renderer, NULL );
}

int sf2d_init_advanced(int gpucmd_size, int temppool_size)
{
	sf2d_init();
}

int sf2d_fini()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
   	SDL_Quit();
}

void sftd_init()
{
	TTF_Init();
}

void sftd_fini()
{
	TTF_Quit();
}

void sf2d_set_clear_color(u32 color)
{
	/* If i'm not mistaken, this function clears both screens so lets clear both of them */
	SDL_SetRenderTarget( renderer, top_screen );
	SDL_SetRenderDrawColor(renderer, RGBA8_GET_R(color), RGBA8_GET_G(color), RGBA8_GET_B(color), RGBA8_GET_A(color));
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_SetRenderTarget( renderer, bottom_screen );
	SDL_SetRenderDrawColor(renderer, RGBA8_GET_R(color), RGBA8_GET_G(color), RGBA8_GET_B(color), RGBA8_GET_A(color));
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	/* The entire screen need to be cleared as well so it looks more consistent with 2 other screens */
	SDL_SetRenderTarget( renderer, NULL );
	SDL_SetRenderDrawColor(renderer, RGBA8_GET_R(color), RGBA8_GET_G(color), RGBA8_GET_B(color), RGBA8_GET_A(color));
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	switch(currentscreen)
	{
		case GFX_TOP:
			SDL_SetRenderTarget( renderer, top_screen );
		break;
		case GFX_BOTTOM:
			SDL_SetRenderTarget( renderer, bottom_screen );
		break;
	}
}

void sf2d_set_vblank_wait(int enable)
{
	/* Always prevent the game from running faster than the display */
	synchro = 1;
}

void sf2d_start_frame(int screentodraw, int wheretodraw)
{
	donotdraw = 0;
	switch(screentodraw)
	{
		case GFX_TOP:
			SDL_SetRenderTarget( renderer, top_screen );
		break;
		case GFX_BOTTOM:
			SDL_SetRenderTarget( renderer, bottom_screen );
		break;
	}
	
	if (screentodraw == GFX_TOP)
	{
		currentscreen = GFX_TOP;
		SDL_SetRenderTarget( renderer, top_screen );
	}
	else if (screentodraw == GFX_BOTTOM)
	{
		currentscreen = GFX_BOTTOM;
		SDL_SetRenderTarget( renderer, bottom_screen );
	}
}

void sf2d_end_frame()
{
	donotdraw = 1;
}

/* https://stackoverflow.com/questions/779875/what-is-the-function-to-replace-string-in-c */
static void replacestr(char *line, const char *search, const char *replace)
{
     char *sp;

     if ((sp = strstr(line, search)) == NULL) {
         return;
     }
     int search_len = strlen(search);
     int replace_len = strlen(replace);
     int tail_len = strlen(sp+search_len);

     memmove(sp+replace_len,sp+search_len,tail_len+1);
     memcpy(sp, replace, replace_len);
}

sf2d_texture *sf2d_create_texture(int width, int height, sf2d_texfmt pixel_format, int itdoesntmatter)
{
	SDL_Texture *texture;
	unsigned long format;
	
	/*
	 * SDL_PIXELFORMAT_ARGB4444
	 * SDL_PIXELFORMAT_RGBA4444
	 * SDL_PIXELFORMAT_ARGB8888
	 * SDL_PIXELFORMAT_RGBA8888
	 * SDL_PIXELFORMAT_RGB24
	 * SDL_PIXELFORMAT_RGB565
	 * SDL_PIXELFORMAT_BGR565
	*/
	
	switch(pixel_format)
	{
		case TEXFMT_RGBA8:
			format = SDL_PIXELFORMAT_ARGB8888;
			//format = SDL_PIXELFORMAT_RGBA888;
		break;
		case TEXFMT_RGB8:
			format = SDL_PIXELFORMAT_RGB24;
		break;
		case TEXFMT_RGB565:
			format = SDL_PIXELFORMAT_RGB565;
		break;
		case TEXFMT_A4:
			format = SDL_PIXELFORMAT_RGBA4444;
		break;
		default:
			format = SDL_PIXELFORMAT_ARGB8888;
			//format = SDL_PIXELFORMAT_RGBA888;
		break;
	}
	texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, width, height);
	
	return texture;
}


sf2d_texture* sfil_load_PNG_file(const char* path, int somebullshitwedontcarefor)
{
	SDL_Surface* tmp;
	SDL_Texture *tmp2;
	char final_path[128];
	
	snprintf(final_path, sizeof(final_path), "%s", path);
	replacestr(final_path, "romfs:/", "./romfs/");

	tmp = IMG_Load(final_path);
	if (tmp)
	{
		SDL_SetSurfaceRLE(tmp, 1);
		tmp2 = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	else
	{
		printf("ERROR, COULD NOT LOAD IMAGE %s !!!\n", path);
		return NULL;
	}
	
	return tmp2;
}

sf2d_texture *sf2d_create_texture_mem_RGBA8(unsigned char *src_buffer, int src_w, int src_h, int pixelformat, int shitnotimplemented)
{
	/* Not yet supported */
	SDL_Surface* tmp;
	SDL_Texture *tmp2;
	SDL_RWops *rw;
	rw = SDL_RWFromMem(src_buffer, (src_w*src_h)*32);
	tmp = SDL_LoadBMP_RW(rw, 0);
	if (rw) SDL_FreeRW(rw);
	
	if (tmp)
	{
		SDL_SetSurfaceRLE(tmp, 1);
		tmp2 = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
	}
	else
	{
		printf("ERROR, COULD NOT LOAD IMAGE !!!\n");
		return NULL;
	}

	return tmp2;
}

void sf2d_texture_tile32(sf2d_texture *texture)
{
	/*if (texture->tiled) return;

	// TODO: add support for non-RGBA8 textures
	u8 *tmp = malloc(texture->tex.width * texture->tex.height * 4);

	int i, j;
	for (j = 0; j < texture->tex.height; j++) {
		for (i = 0; i < texture->tex.width; i++) {

			u32 coarse_y = j & ~7;
			u32 dst_offset = get_morton_offset(i, j, 4) + coarse_y * texture->tex.width * 4;

			u32 v = ((u32 *)texture->tex.data)[i + (texture->tex.height - 1 - j)*texture->tex.width];
			*(u32 *)(tmp + dst_offset) = __builtin_bswap32(v);
		}
	}

	memcpy(texture->tex.data, tmp, texture->tex.width*texture->tex.height*4);
	if (tmp) free(tmp);*/
}


sftd_font* sftd_load_font_file(const char* path)
{
	TTF_Font* font;
	char final_path[128];
	
	snprintf(final_path, sizeof(final_path), "%s", path);
	replacestr(final_path, "romfs:/", "./romfs/");
	
	font = TTF_OpenFont(final_path, 20);
	if (font)
	{
		return font;
	}
	else
	{
		printf("ERROR, COULD NOT LOAD FONT %s !!!\n", path);
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		return NULL;
	}
}

void sf2d_draw_texture(sf2d_texture *yourmom, int x, int y)
{
	int w, h;
	SDL_QueryTexture(yourmom, NULL, NULL, &w, &h);

	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
	SDL_RenderCopy(renderer, yourmom, NULL, &position);
}

void sf2d_draw_texture_rotate(sf2d_texture *texture, int x, int y, float rad)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Point center;
	center.x = 0;
	center.y = 0;
	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
	SDL_RenderCopyEx(renderer, texture, NULL, &position, rad, &center, SDL_FLIP_NONE);
}

void sf2d_draw_texture_scale(sf2d_texture *texture, int x, int y, float x_scale, float y_scale)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = (float)(w * x_scale);
	position.h = (float)(h * y_scale);
	SDL_RenderCopy(renderer, texture, NULL, &position);
}

void sf2d_draw_texture_part(sf2d_texture *texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
	
	SDL_Rect frame;
	frame.x = tex_x;
	frame.y = tex_y;
	frame.w = tex_w;
	frame.h = tex_h;
	
	SDL_RenderCopy(renderer, texture, &frame, &position);
}

void sf2d_draw_texture_part_scale(sf2d_texture *texture, float x, float y, float tex_x, float tex_y, float tex_w, float tex_h, float x_scale, float y_scale)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = (float)(w * x_scale);
	position.h = (float)(h * y_scale);
	
	SDL_Rect frame;
	frame.x = tex_x;
	frame.y = tex_y;
	frame.w = tex_w;
	frame.h = tex_h;
	
	SDL_RenderCopy(renderer, texture, &frame, &position);
}

void sf2d_draw_texture_part_rotate_scale(sf2d_texture *texture, int x, int y, float rad, int tex_x, int tex_y, int tex_w, int tex_h, float x_scale, float y_scale)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Point center;
	center.x = 0;
	center.y = 0;
	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = (float)(w * x_scale);
	position.h = (float)(h * y_scale);
	
	SDL_Rect frame;
	frame.x = tex_x;
	frame.y = tex_y;
	frame.w = tex_w;
	frame.h = tex_h;
	
	SDL_RenderCopyEx(renderer, texture, &frame, &position, rad, &center, SDL_FLIP_NONE);
}

void sf2d_draw_texture_part_scale_blend(sf2d_texture *texture, float x, float y, float tex_x, float tex_y, float tex_w, float tex_h, float x_scale, float y_scale, u32 color)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = (float)(w * x_scale);
	position.h = (float)(h * y_scale);
	
	SDL_Rect frame;
	frame.x = tex_x;
	frame.y = tex_y;
	frame.w = tex_w;
	frame.h = tex_h;
	
	SDL_SetTextureColorMod(texture, RGBA8_GET_R(color)-255, RGBA8_GET_G(color)-255, RGBA8_GET_B(color)-255);
	SDL_RenderCopy(renderer, texture, &frame, &position);
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void sf2d_draw_texture_rotate_cut_scale(sf2d_texture *texture, int x, int y, float rad, int tex_x, int tex_y, int tex_w, int tex_h, float x_scale, float y_scale)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Point center;
	center.x = 0;
	center.y = 0;
	
	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = (float)(w * x_scale);
	position.h = (float)(h * y_scale);
	
	SDL_Rect frame;
	frame.x = tex_x;
	frame.y = tex_y;
	frame.w = tex_w;
	frame.h = tex_h;
	
	SDL_RenderCopyEx(renderer, texture, &frame, &position, rad, &center, SDL_FLIP_NONE);
}

void sf2d_draw_texture_blend(sf2d_texture *texture, int x, int y, u32 color)
{
	int w, h;
	SDL_Rect position;
	
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
	
	SDL_SetTextureColorMod(texture, RGBA8_GET_R(color)-255, RGBA8_GET_G(color)-255, RGBA8_GET_B(color)-255);
	SDL_RenderCopy(renderer, texture, NULL, &position);
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void sf2d_draw_texture_part_blend(sf2d_texture *texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h, u32 color)
{
	int w, h;
	SDL_Rect position, frame;
	
	SDL_SetTextureColorMod(texture, RGBA8_GET_R(color)-255, RGBA8_GET_G(color)-255, RGBA8_GET_B(color)-255);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
	
	frame.x = tex_x;
	frame.y = tex_y;
	frame.w = tex_w;
	frame.h = tex_h;
	
	SDL_RenderCopy(renderer, texture, &frame, &position);
	
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void sf2d_draw_texture_depth (sf2d_texture *texture, int x, int y, signed short z)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect position;
	SDL_Point center;
	
	center.x = w / 2;
	center.y = h / 2;
	
	position.x = x;
	position.y = y;
	position.w = (float)(w * (z / sizeof(short)));
	position.h = (float)(h * (z / sizeof(short)));
	
	SDL_RenderCopyEx(renderer, texture, NULL, &position, 0.0f, &center, SDL_FLIP_NONE);
}



void sftd_draw_textf(sftd_font *font, int x, int y, u32 color, int size, const char* string_text)
{
	int w, h;
	SDL_Texture* resulting_text;
	SDL_Surface *tmp;
	
	SDL_Rect position;
	
	SDL_Color clr= { RGBA8_GET_R(color), RGBA8_GET_G(color), RGBA8_GET_B(color)};

	tmp = TTF_RenderText_Blended(font, string_text, clr);
	SDL_SetSurfaceRLE(tmp, 1);
	resulting_text = SDL_CreateTextureFromSurface(renderer, tmp);
	
	SDL_QueryTexture(resulting_text, NULL, NULL, &w, &h);
	
	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
	
	SDL_RenderCopy(renderer, resulting_text, NULL, &position);
	SDL_FreeSurface(tmp);
	SDL_DestroyTexture(resulting_text);
}

void sf2d_free_texture(sf2d_texture *texture)
{
	SDL_DestroyTexture(texture);
}

void sftd_free_font(sftd_font* ex)
{
	TTF_CloseFont(ex);
}

void sf2d_swapbuffers()
{
	SDL_SetRenderTarget(renderer, NULL);
	SDL_Rect position, bottom_pos;
	position.x = 0;
	position.y = 0;
	position.w = 400;
	position.h = 240;
	bottom_pos.x = 40;
	bottom_pos.y = 240;
	bottom_pos.w = 320;
	bottom_pos.h = 240;
	SDL_RenderCopy(renderer, top_screen, NULL, &position);
	SDL_RenderCopy(renderer, bottom_screen, NULL, &bottom_pos);
	SDL_RenderPresent(renderer);
}

gfxScreen_t sf2d_get_current_screen()
{
	return currentscreen;
}

gfxScreen_t sf2d_get_current_side()
{
	return 0;
}

void sf2d_draw_line(int x0, int y0, int x1, int y1, u32 color)
{
	lineColor(renderer, x0, y1, x1, y1, color);
}

void sf2d_draw_rectangle(int x, int y, int w, int h, u32 color)
{
	SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
	
	SDL_SetRenderDrawColor( renderer, RGBA8_GET_R(color), RGBA8_GET_G(color), RGBA8_GET_B(color), RGBA8_GET_A(color));
	SDL_RenderFillRect( renderer, &r );
}


void sf2d_draw_rectangle_rotate(int x, int y, int w, int h, u32 color, float rad)
{
	SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
	
	SDL_SetRenderDrawColor( renderer, RGBA8_GET_R(color), RGBA8_GET_G(color), RGBA8_GET_B(color), RGBA8_GET_A(color));
	SDL_RenderFillRect( renderer, &r );
}


void sf2d_draw_triangle(float x1, float y1, float x2, float y2, float x3, float y3, u32 color)
{
	trigonRGBA(renderer,
               (short)x1, (short)y1,
               (short)x2, (short)y2,
               (short)x3, (short)y3,
               RGBA8_GET_R(color), RGBA8_GET_G(color), RGBA8_GET_B(color), RGBA8_GET_A(color));
}

void sf2d_draw_fill_circle(int rad, int x, int y, u32 color)
{
	result = circleColor(renderer, x, y, rad, color);
}

void sf2d_set_pixel (sf2d_texture *texture, int x, int y, u32 new_color)
{
	/* TODO : Needs to be optimised with SDL_LockTexture */
	int w, h;
	Uint32 *pixels;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	pixels = malloc(w*h);
	pixels[y * w + x] = new_color;
	SDL_UpdateTexture(texture, NULL, pixels, w * sizeof(Uint32));
}

u32 sf2d_get_pixel(sf2d_texture *texture, int x, int y)
{
	/* FIXME : TODO */
	/*
	SDL_SetRenderTarget(renderer, target);
	SDL_RenderReadPixels(renderer, rect, format, pixels, pitch);
	*/
}

unsigned int sf2d_pool_space_free()
{
	return 1;
}

void sf2d_pool_reset()
{
	printf("nigga is trying to pool reset\n");
}

void sf2d_set_3D(u8 enable)
{
	if (enable)
	{
		printf("There is no 3D on PC and it is not going to be implemented anytime soon, if ever.\n");
	}
}

float sf2d_get_fps ()
{
	return 60.0f;
}

// Grabbed from Citra Emulator (citra/src/video_core/utils.h)
static inline u32 morton_interleave(u32 x, u32 y)
{
	u32 i = (x & 7) | ((y & 7) << 8); // ---- -210
	i = (i ^ (i << 2)) & 0x1313;      // ---2 --10
	i = (i ^ (i << 1)) & 0x1515;      // ---2 -1-0
	i = (i | (i >> 7)) & 0x3F;
	return i;
}

//Grabbed from Citra Emulator (citra/src/video_core/utils.h)
static inline u32 get_morton_offset(u32 x, u32 y, u32 bytes_per_pixel)
{
    u32 i = morton_interleave(x, y);
    unsigned int offset = (x & ~7) * 8;
    return (i + offset) * bytes_per_pixel;
}
