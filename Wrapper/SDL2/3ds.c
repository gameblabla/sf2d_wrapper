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
