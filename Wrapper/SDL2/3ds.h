/*

The MIT License (MIT)

Copyright (c) 2016 Gameblabla

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

*/

#ifndef THREEDS_DEFINE
#define THREEDS_DEFINE

#include <SDL.h>
typedef struct
{
	unsigned short px; ///< Touch X
	unsigned short py; ///< Touch Y
} touchPosition;


#define u8 unsigned char
#define s8 signed char
#define u16 unsigned short
#define s16 signed short
#define s32 signed long
#define u32 unsigned long
#define u64 unsigned long long
#define bool u8

/// Creates a bitmask from a bit number.
#define BIT(n) (1U<<(n))
#define Result signed int

enum
{
	KEY_A       = BIT(0),       ///< A
	KEY_B       = BIT(1),       ///< B
	KEY_SELECT  = BIT(2),       ///< Select
	KEY_START   = BIT(3),       ///< Start
	KEY_DRIGHT  = BIT(4),       ///< D-Pad Right
	KEY_DLEFT   = BIT(5),       ///< D-Pad Left
	KEY_DUP     = BIT(6),       ///< D-Pad Up
	KEY_DDOWN   = BIT(7),       ///< D-Pad Down
	KEY_R       = BIT(8),       ///< R
	KEY_L       = BIT(9),       ///< L
	KEY_X       = BIT(10),      ///< X
	KEY_Y       = BIT(11),      ///< Y
	KEY_ZL      = BIT(14),      ///< ZL (New 3DS only)
	KEY_ZR      = BIT(15),      ///< ZR (New 3DS only)
	KEY_TOUCH   = BIT(20),      ///< Touch (Not actually provided by HID)
	KEY_CSTICK_RIGHT = BIT(24), ///< C-Stick Right (New 3DS only)
	KEY_CSTICK_LEFT  = BIT(25), ///< C-Stick Left (New 3DS only)
	KEY_CSTICK_UP    = BIT(26), ///< C-Stick Up (New 3DS only)
	KEY_CSTICK_DOWN  = BIT(27), ///< C-Stick Down (New 3DS only)
	KEY_CPAD_RIGHT = BIT(28),   ///< Circle Pad Right
	KEY_CPAD_LEFT  = BIT(29),   ///< Circle Pad Left
	KEY_CPAD_UP    = BIT(30),   ///< Circle Pad Up
	KEY_CPAD_DOWN  = BIT(31),   ///< Circle Pad Down

	// Generic catch-all directions
	KEY_UP    = KEY_DUP    | KEY_CPAD_UP,    ///< D-Pad Up or Circle Pad Up
	KEY_DOWN  = KEY_DDOWN  | KEY_CPAD_DOWN,  ///< D-Pad Down or Circle Pad Down
	KEY_LEFT  = KEY_DLEFT  | KEY_CPAD_LEFT,  ///< D-Pad Left or Circle Pad Left
	KEY_RIGHT = KEY_DRIGHT | KEY_CPAD_RIGHT, ///< D-Pad Right or Circle Pad Right
};

void hidScanInput(void);
u32 hidKeysDown(void);
void hidTouchRead(touchPosition* touch);

void romfsInit();
void romfsExit();

int aptMainLoop();

/* os specific functions*/

u64 osGetTime(void);
void osSetSpeedupEnable(bool enable);

/* cfg stuff */
Result cfguInit(void);
Result CFGU_GetSystemModel(u8* model);
void cfguExit(void);

/*
 * GPU stuff
 * 
*/

#define GPU_NEVER 0
#define GPU_STENCIL_REPLACE 0
#define GPU_STENCIL_KEEP 0
#define GPU_GREATER 0
#define GPU_GEQUAL 0
#define GPU_WRITE_ALL 0
#define GPU_EQUAL 0
#define GPU_ALWAYS 0
#define GPU_STENCIL_KEEP 0


Result GSPGPU_FlushDataCache(const void* adr, u32 size);
int GPU_SetDepthTestAndWriteMask(int enable, int gpu_state, int stub1);
int GPU_SetStencilTest(int enable, int gpu_state, int stub1, int stub2, int stub3);
int GPU_SetAlphaTest(int enable, int gpu_state, int stub1);
int GPU_SetStencilOp(int enable, int gpu_state, int stub1);

/*
 * Memory stuff 
*/

void linearFree(void* mem);
void* linearAlloc(size_t size);
void* linearMemAlign(size_t size, size_t alignment);
void* linearRealloc(void* mem, size_t size);

/*
 * 
 * Sound related stuff
 * 
*/
Result csndPlaySound(int chn, u32 flags, u32 sampleRate, float vol, float pan, void* data0, void* data1, u32 size);
void csndInit();
void csndExit();
void csndExecCmds(unsigned char enable);
void CSND_SetPlayState(u32 channel, u32 value);


/*
 * This is directly taken from the header csnd.h
*/

/// Creates a sound channel value from a channel number.
#define SOUND_CHANNEL(n) ((u32)(n) & 0x1F)

/// Creates a sound format value from an encoding.
#define SOUND_FORMAT(n) ((u32)(n) << 12)

/// Creates a sound loop mode value from a loop mode.
#define SOUND_LOOPMODE(n) ((u32)(n) << 10)

enum
{
	CSND_ENCODING_PCM8 = 0, ///< PCM8
	CSND_ENCODING_PCM16,    ///< PCM16
	CSND_ENCODING_ADPCM,    ///< IMA-ADPCM
	CSND_ENCODING_PSG,      ///< PSG (Similar to DS?)
};

enum
{
	CSND_LOOPMODE_MANUAL = 0, ///< Manual loop.
	CSND_LOOPMODE_NORMAL,     ///< Normal loop.
	CSND_LOOPMODE_ONESHOT,    ///< Do not loop.
	CSND_LOOPMODE_NORELOAD,   ///< Don't reload.
};

enum
{
	SOUND_LINEAR_INTERP = BIT(6),                           ///< Linear interpolation.
	SOUND_REPEAT = SOUND_LOOPMODE(CSND_LOOPMODE_NORMAL),    ///< Repeat the sound.
	SOUND_ONE_SHOT = SOUND_LOOPMODE(CSND_LOOPMODE_ONESHOT), ///< Play the sound once.
	SOUND_FORMAT_8BIT = SOUND_FORMAT(CSND_ENCODING_PCM8),   ///< PCM8
	SOUND_FORMAT_16BIT = SOUND_FORMAT(CSND_ENCODING_PCM16), ///< PCM16
	SOUND_FORMAT_ADPCM = SOUND_FORMAT(CSND_ENCODING_ADPCM), ///< ADPCM
	SOUND_FORMAT_PSG = SOUND_FORMAT(CSND_ENCODING_PSG),     ///< PSG
	SOUND_ENABLE = BIT(14),                                 ///< Enable sound.
};

#endif
