/*

The MIT License (MIT)

Copyright (c) 2016 Gameblabla

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <time.h>
#include <sys/time.h>

static u32 kHeld = 0, kDown = 0, kUp = 0;

int hidInit(void)
{
}

void hidScanInput(void)
{
}

void romfsInit()
{
}

void romfsExit()
{
}

/* cfg, 3ds-specific again (not very useful) */
Result cfguInit(void)
{
	return 1;
}

Result CFGU_GetSystemModel(u8* model)
{
	return 1;
}

void cfguExit(void)
{
}

/* Sound stuff */
Result csndPlaySound(int chn, u32 flags, u32 sampleRate, float vol, float pan, void* data0, void* data1, u32 size)
{	
}

void csndInit()
{
	
}

void csndExit()
{
	
}

void csndExecCmds(unsigned char enable)
{
}

void CSND_SetPlayState(u32 channel, u32 value)
{
}

/* The new GPU API, sometimes used for non-GPU stuff */

Result GSPGPU_FlushDataCache(const void* adr, u32 size)
{
}

/* The old GPU Api, still used by some old 3DS homebrew games apparently */

int GPU_SetDepthTestAndWriteMask(int enable, int gpu_state, int stub1)
{
}

int GPU_SetStencilTest(int enable, int gpu_state, int stub1, int stub2, int stub3)
{
}

int GPU_SetAlphaTest(int enable, int gpu_state, int stub1)
{
}

int GPU_SetStencilOp(int enable, int gpu_state, int stub1)
{
}

void linearFree(void* mem)
{
	if (mem) free(mem);
}

void* linearAlloc(size_t size)
{
	return linearMemAlign(size, 0x80);
}

void* linearMemAlign(size_t size, size_t alignment)
{
	return aligned_alloc(alignment, size);
}

/* According to libctru, this isn't actually implemented yet as for 2016 */
void* linearRealloc(void* mem, size_t size)
{
	return NULL;
}

int aptMainLoop()
{
	return 1;
}

u32 hidKeysHeld(void)
{
	return kHeld;
}

u32 hidKeysDown(void)
{
	return kDown;
}

u32 hidKeysUp(void)
{
	return kUp;
}

u64 osGetTime(void)
{
	return time(0)*1000;
}

void osSetSpeedupEnable(bool enable)
{
	/* Only useful on 3DS */
}

void hidTouchRead(touchPosition* pos)
{
	touchPosition touch;
	SDL_Event event;
	
	touch.px = 0;
	touch.py = 0;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				if (event.motion.x > 40 && event.motion.y > 240)
				{
					/*printf("Pressing my penis against the screen\n");*/
					touch.px = event.motion.x-40;
					touch.py = event.motion.y-240;
					kDown |= KEY_TOUCH;
					kHeld |= KEY_TOUCH;
					kUp &= KEY_TOUCH;
				}
			break;
			case SDL_MOUSEBUTTONUP:
				if (event.motion.x > 40 && event.motion.y > 240)
				{
					/*printf("RELEASE THE BOGUS\n");*/
					touch.px = event.motion.x-40;
					touch.py = event.motion.y-240;
					kUp |= KEY_TOUCH;
					kDown &= KEY_TOUCH;
					kHeld &= KEY_TOUCH;
				}
			break;
			case SDL_KEYDOWN:
				switch (SDL_GetScancodeFromKey(event.key.keysym.sym))
				{
					case SDL_SCANCODE_UP: 
						kDown |= KEY_UP;
						kHeld |= KEY_UP;
						kUp &= KEY_UP;
					break;
					case SDL_SCANCODE_DOWN: 
						kDown |= KEY_DOWN;
						kHeld |= KEY_DOWN;
						kUp &= KEY_DOWN;
					break;
					case SDL_SCANCODE_LEFT: 
						kDown |= KEY_LEFT;
						kHeld |= KEY_LEFT;
						kUp &= KEY_LEFT;
					break;
					case SDL_SCANCODE_RIGHT: 
						kDown |= KEY_RIGHT;
						kHeld |= KEY_RIGHT;
						kUp &= KEY_RIGHT;
					break;	
					case SDL_SCANCODE_LCTRL: 
						kDown |= KEY_A;
						kHeld |= KEY_A;
						kUp &= KEY_A;
					break;
					case SDL_SCANCODE_LALT: 
						kDown |= KEY_B;
						kHeld |= KEY_B;
						kUp &= KEY_B;
					break;
					case SDL_SCANCODE_LSHIFT: 
						kDown |= KEY_X;
						kHeld |= KEY_X;
						kUp &= KEY_X;
					break;
					case SDL_SCANCODE_SPACE: 
						kDown |= KEY_Y;
						kHeld |= KEY_Y;
						kUp &= KEY_Y;
					break;
					case SDL_SCANCODE_TAB: 
						kDown |= KEY_L;
						kHeld |= KEY_L;
						kUp &= KEY_L;
					break;
					case SDL_SCANCODE_BACKSPACE: 
						kDown |= KEY_R;
						kHeld |= KEY_R;
						kUp &= KEY_R;
					break;
					case SDL_SCANCODE_ESCAPE: 
						kDown |= KEY_SELECT;
						kHeld |= KEY_SELECT;
						kUp &= KEY_SELECT;
					break;
					case SDL_SCANCODE_RETURN: 
						kDown |= KEY_START;
						kHeld |= KEY_START;
						kUp &= KEY_START;
					break;
				}
			break;
			case SDL_KEYUP:
				switch (SDL_GetScancodeFromKey(event.key.keysym.sym))
				{
					case SDL_SCANCODE_UP: 
						kDown &= KEY_UP;
						kHeld &= KEY_UP;
						kUp |= KEY_UP;
					break;
					case SDL_SCANCODE_DOWN: 
						kDown &= KEY_DOWN;
						kHeld &= KEY_DOWN;
						kUp |= KEY_DOWN;
					break;
					case SDL_SCANCODE_LEFT: 
						kDown &= KEY_LEFT;
						kHeld &= KEY_LEFT;
						kUp |= KEY_LEFT;
					break;
					case SDL_SCANCODE_RIGHT: 
						kDown &= KEY_RIGHT;
						kHeld &= KEY_RIGHT;
						kUp |= KEY_RIGHT;
					break;	
					case SDL_SCANCODE_LCTRL: 
						kDown &= KEY_A;
						kHeld &= KEY_A;
						kUp |= KEY_A;
					break;
					case SDL_SCANCODE_LALT: 
						kDown &= KEY_B;
						kHeld &= KEY_B;
						kUp |= KEY_B;
					break;
					case SDL_SCANCODE_LSHIFT: 
						kDown &= KEY_X;
						kHeld &= KEY_X;
						kUp |= KEY_X;
					break;
					case SDL_SCANCODE_SPACE: 
						kDown &= KEY_Y;
						kHeld &= KEY_Y;
						kUp |= KEY_Y;
					break;
					case SDL_SCANCODE_TAB: 
						kDown &= KEY_L;
						kHeld &= KEY_L;
						kUp |= KEY_L;
					break;
					case SDL_SCANCODE_BACKSPACE: 
						kDown &= KEY_R;
						kHeld &= KEY_R;
						kUp |= KEY_R;
					break;
					case SDL_SCANCODE_ESCAPE: 
						kDown &= KEY_SELECT;
						kHeld &= KEY_SELECT;
						kUp |= KEY_SELECT;
					break;
					case SDL_SCANCODE_RETURN: 
						kDown &= KEY_START;
						kHeld &= KEY_START;
						kUp |= KEY_START;
					break;
				}
			break;
			case SDL_QUIT:
				exit(1);
			break;
		}
	}    
	
	if (pos) *pos = touch;
}
