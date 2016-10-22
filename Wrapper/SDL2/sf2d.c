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
static SDL_Texture *top_screen, *bottom_screen, *swap_screen;

static const float real_FPS = 1000/60;

static u8 result;
static u8 donotdraw = 0;
static u8 synchro = 1;
static u8 currentscreen = GFX_TOP;
static int currentscreen_x = 0, currentscreen_y = 0;

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
	SDL_SetRenderDrawColor(renderer, RGBA8_GET_R(color), RGBA8_GET_G(color), RGBA8_GET_B(color), RGBA8_GET_A(color));
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void sf2d_set_vblank_wait(int enable)
{
	/* Always prevent the game from running faster than display */
	synchro = 1;
}

void sf2d_start_frame(int screentodraw, int wheretodraw)
{
	donotdraw = 0;
	
	if (screentodraw == GFX_TOP)
	{
		currentscreen = GFX_TOP;
		currentscreen_x = 0;
		currentscreen_y = 0;
	}
	else if (screentodraw == GFX_BOTTOM)
	{
		currentscreen = GFX_BOTTOM;
		currentscreen_x = 40;
		currentscreen_y = 240;
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
	
	/*SDL_Surface *tmp; 
	SDL_Surface *tmp2;
	SDL_RWops *rw;
	rw = SDL_RWFromMem(src_buffer, (src_w*src_h)*32);
	tmp = SDL_LoadBMP_RW(rw, 0);
	SDL_FreeRW(rw);
	
	if (tmp)
	{
		tmp2 = SDL_DisplayFormatAlpha(tmp);
	}
	else
	{
		printf("ERROR, COULD NOT LOAD IMAGE !!!\n");
		return NULL;
	}
	
	return tmp2;*/
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
	position.x = x + currentscreen_x;
	position.y = y + currentscreen_y;
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
	position.x = x + currentscreen_x;
	position.y = y + currentscreen_y;
	position.w = w;
	position.h = h;
	SDL_RenderCopyEx(renderer, texture, NULL, &position, rad, &center, SDL_FLIP_NONE);
}

void sf2d_draw_texture_scale(sf2d_texture *texture, int x, int y, float x_scale, float y_scale)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect position;
	position.x = x + currentscreen_x;
	position.y = y + currentscreen_y;
	position.w = (float)(w * x_scale);
	position.h = (float)(h * y_scale);
	SDL_RenderCopy(renderer, texture, NULL, &position);
}

void sf2d_draw_texture_part(sf2d_texture *texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect position;
	position.x = x + currentscreen_x;
	position.y = y + currentscreen_y;
	position.w = w;
	position.h = h;
	
	SDL_Rect frame;
	frame.x = tex_x;
	frame.y = tex_y;
	frame.w = tex_w;
	frame.h = tex_h;
	
	SDL_RenderCopy(renderer, texture, &frame, &position);
}

void sf2d_draw_texture_rotate_cut_scale(sf2d_texture *texture, int x, int y, float rad, int tex_x, int tex_y, int tex_w, int tex_h, float x_scale, float y_scale)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Point center;
	center.x = 0;
	center.y = 0;
	
	SDL_Rect position;
	position.x = x + currentscreen_x;
	position.y = y + currentscreen_y;
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
	
	SDL_SetTextureColorMod(texture, RGBA8_GET_R(color)-255, RGBA8_GET_G(color)-255, RGBA8_GET_B(color)-255);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	position.x = x + currentscreen_x;
	position.y = y + currentscreen_y;
	position.w = w;
	position.h = h;
	SDL_RenderCopy(renderer, texture, NULL, &position);
	
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void sf2d_draw_texture_part_blend(sf2d_texture *texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h, u32 color)
{
	int w, h;
	SDL_Rect position, frame;
	
	SDL_SetTextureColorMod(texture, RGBA8_GET_R(color)-255, RGBA8_GET_G(color)-255, RGBA8_GET_B(color)-255);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	position.x = x + currentscreen_x;
	position.y = y + currentscreen_y;
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
	
	position.x = x + currentscreen_x;
	position.y = y + currentscreen_y;
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
	
	position.x = x + currentscreen_x;
	position.y = y + currentscreen_y;
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
