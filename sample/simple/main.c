
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <3ds.h>
#include <sf2d.h>

int main()
{
    sf2d_init();
    sf2d_set_clear_color(RGBA8(0x00, 0x00, 0x00, 0x00));

    while (aptMainLoop()) {

        hidScanInput();
        if (hidKeysDown() & KEY_START) break;

        sf2d_start_frame(GFX_TOP, GFX_LEFT);
            //Draws a 100x100 yellow rectangle (255, 255, 00, 255) at (150, 70)
            sf2d_draw_rectangle(150, 70, 100, 100, RGBA8(0xFF, 0xFF, 0x00, 0xFF));
        sf2d_end_frame();

        sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
            //Draws a 70x100 blue rectangle (0, 0, 00, 255) at (120, 30)
            sf2d_draw_rectangle(120, 30, 70, 100, RGBA8(0x00, 0x00, 0xFF, 0xFF));
        sf2d_end_frame();

        sf2d_swapbuffers();
    }

    sf2d_fini();
    return 0;
}
