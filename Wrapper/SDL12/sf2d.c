/*

The MIT License (MIT)

Copyright (c) 2016 Gameblabla

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

*/

#include "sf2d.h"

static SDL_Surface *screen, *top_screen, *bottom_screen, *swap_screen;
static const float real_FPS = 1000/60;

static u8 result;
static u8 donotdraw = 0;
static u8 synchro = 1;
static u8 currentscreen = GFX_TOP;

u8 fontsize;

int sf2d_init()
{
	SDL_Init( SDL_INIT_VIDEO );
	SDL_ShowCursor(SDL_TRUE);
	screen = SDL_SetVideoMode(400, 480, 32, SDL_HWSURFACE);
	
	top_screen = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 240, 32, 0,0,0,0);
	bottom_screen = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0,0,0,0);
	swap_screen = top_screen;
}

int sf2d_init_advanced(int gpucmd_size, int temppool_size)
{
	sf2d_init();
}

int sf2d_fini()
{
	if (bottom_screen) SDL_FreeSurface(bottom_screen);
	if (top_screen) SDL_FreeSurface(top_screen);
	if (screen) SDL_FreeSurface(screen);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
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
	SDL_LockSurface(top_screen);
	SDL_LockSurface(bottom_screen);
	SDL_LockSurface(screen);
	SDL_FillRect(bottom_screen, NULL, color);
	SDL_FillRect(top_screen, NULL, color);
	SDL_FillRect(screen, NULL, color);
	SDL_UnlockSurface(top_screen);
	SDL_UnlockSurface(bottom_screen);
	SDL_UnlockSurface(screen);
}

void sf2d_set_vblank_wait(int enable)
{
	/* Always prevent the game from running faster than display */
	synchro = 1;
	/*if (enable)
	{
		synchro = 1;
	}
	else
	{
		synchro = 0;
	}*/
}

void sf2d_start_frame(int screentodraw, int wheretodraw)
{
	donotdraw = 0;
	
	if (screentodraw == GFX_TOP)
	{
		swap_screen = top_screen;
		currentscreen = GFX_TOP;
	}
	else if (screentodraw == GFX_BOTTOM)
	{
		swap_screen = bottom_screen;
		currentscreen = GFX_BOTTOM;
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
	SDL_Surface *tmp, *tmp2; 
	char final_path[128];
	
	snprintf(final_path, sizeof(final_path), "%s", path);
	replacestr(final_path, "romfs:/", "./romfs/");

	tmp = IMG_Load(final_path);
	if (tmp)
	{
		tmp2 = SDL_DisplayFormatAlpha(tmp);
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
	SDL_Surface *tmp; 
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
	
	return tmp2;
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
	SDL_Rect position;
	position.x = x;
	position.y = y;
	SDL_BlitSurface(yourmom, NULL, swap_screen, &position);
}

void sf2d_draw_texture_depth (sf2d_texture *texture, int x, int y, signed short z)
{
	sf2d_draw_texture(texture, x, y);
}

void sf2d_draw_texture_part(sf2d_texture *texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h)
{
	SDL_Rect position;
	position.x = x;
	position.y = y;

	SDL_Rect frame;
	frame.x = tex_x;
	frame.y = tex_y;
	frame.w = tex_w;
	frame.h = tex_h;

	SDL_BlitSurface(texture, &frame, swap_screen, &position);
}



void sftd_draw_textf(sftd_font *font, int x, int y, u32 color, int size, const char* string_text)
{
	SDL_Surface* resulting_text;
	SDL_Surface *tmp;
	
	SDL_Rect position;
	position.x = x;
	position.y = y;
	
	SDL_Color clr= { RGBA8_GET_R(color), RGBA8_GET_G(color), RGBA8_GET_B(color)};

	tmp = TTF_RenderText_Blended(font, string_text, clr);
	resulting_text = SDL_DisplayFormatAlpha(tmp);
	
	SDL_BlitSurface(resulting_text, NULL, swap_screen, &position);
	SDL_FreeSurface(resulting_text);
	SDL_FreeSurface(tmp);
}

void sf2d_free_texture(sf2d_texture *texture)
{
	SDL_FreeSurface(texture);
}

void sftd_free_font(sftd_font* ex)
{
	TTF_CloseFont(ex);
}

static void msleep(unsigned char milisec)
{
	#ifdef UNIX
		struct timespec req={0};
		time_t sec=(unsigned short)(milisec/1000);

		milisec=milisec-(sec*1000);
		req.tv_sec=sec;
		req.tv_nsec=milisec*1000000L;

		while(nanosleep(&req,&req)==-1)
		continue;
	#else
		SDL_Delay(milisec);
	#endif
}

void sf2d_swapbuffers()
{
	u32 start;
	if (synchro)
	{
		start = SDL_GetTicks();
		if(60 > SDL_GetTicks()-start) msleep(60-(SDL_GetTicks()-start));
	}
	
	SDL_Rect position, position_bottom;
	position.x = 0;
	position.y = 0;
	position_bottom.x = 40;
	position_bottom.y = 240;
	SDL_BlitSurface(top_screen, NULL, screen, &position);
	SDL_BlitSurface(bottom_screen, NULL, screen, &position_bottom);
	SDL_Flip(screen);
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
	lineColor(swap_screen, x0, y1, x1, y1, color);
}

void sf2d_draw_rectangle(int x, int y, int w, int h, u32 color)
{
	SDL_Rect scr_draw;
	scr_draw.x = x;
	scr_draw.y = y;
	scr_draw.w = w;
	scr_draw.h = h;
	
	SDL_LockSurface(swap_screen);
	SDL_FillRect(swap_screen, &scr_draw, color);
	SDL_UnlockSurface(swap_screen);
}

void sf2d_draw_triangle(float x1, float y1, float x2, float y2, float x3, float y3, u32 color)
{
	trigonRGBA(swap_screen,
               (short)x1, (short)y1,
               (short)x2, (short)y2,
               (short)x3, (short)y3,
               RGBA8_GET_R(color), RGBA8_GET_G(color), RGBA8_GET_B(color), RGBA8_GET_A(color));
}

void sf2d_draw_fill_circle(int rad, int x, int y, u32 color)
{
	result = circleColor(swap_screen, x, y, rad, color);
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
