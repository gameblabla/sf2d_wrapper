#include <sf2d.h>
#include <sftd.h>
#include <sfil.h>
#include <string.h>
#include <stdio.h>
#include "graphics.h"

//With x and y, load images in the correct location
int tabPosX[6] = {0, 5, 66, 127, 188, 249};
int tabPosY[5] = {0, 0, 61, 122, 183};
char string[16]; //char tab that contains string

// declaring graphic elements
sftd_font *font; 
sf2d_texture *backgroundTexture;
sf2d_texture *image0;
sf2d_texture *image1;
sf2d_texture *image2;
sf2d_texture *image3;
sf2d_texture *image4;
sf2d_texture *image5;
sf2d_texture *image6;
sf2d_texture *image7;
sf2d_texture *image8;
sf2d_texture *image9;
sf2d_texture *image10;

bool FileExists(const char *filename) { //This will return true if the file exists and if the header is a PNG with 56*56 dimensions
	FILE *fp = fopen (filename, "rb");
	if (fp!=NULL) { //If fp!=NULL, so == 1, true, the file exists
		char ImagePNGHeader[40]; //string that will contains the first 24 bytes of the file
		unsigned char sig[24];
		fread(sig, 1, 24, fp); //Read first 24 bytes, and put that into sig
		sprintf(ImagePNGHeader, "%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i", sig[0], sig[1], sig[2], sig[3], sig[4], sig[5], sig[6], sig[7], sig[8], sig[9], sig[10], sig[11], sig[12], sig[13], sig[14], sig[15], sig[16], sig[17], sig[18], sig[19], sig[20], sig[21], sig[22], sig[23]);//Convert sig to string into ImagePNGHeader
		if(strcmp(ImagePNGHeader, "1378078711310261000013737268820005600056") == 0) { //If the file is a PNG with 56*56 dimensions
			fclose (fp);
			return true;
		}
		else { //The file exists, but not a PNG / 56*56
			fclose (fp);
			return false;
		}	
	}
	else { //The file doesn't exist
		fclose (fp);
		return false;
	}
}

// initialization of textures
void GUIElementsInit() {
	if (FileExists("sdmc:/3ds/data/Memory3DS/0.png")) {image0 = sfil_load_PNG_file("sdmc:/3ds/data/Memory3DS/0.png", SF2D_PLACE_RAM);} else {image0 = sfil_load_PNG_file("romfs:/0.png", SF2D_PLACE_RAM);}
	if (FileExists("sdmc:/3ds/data/Memory3DS/1.png")) {image1 = sfil_load_PNG_file("sdmc:/3ds/data/Memory3DS/1.png", SF2D_PLACE_RAM);} else {image1 = sfil_load_PNG_file("romfs:/1.png", SF2D_PLACE_RAM);}
	if (FileExists("sdmc:/3ds/data/Memory3DS/2.png")) {image2 = sfil_load_PNG_file("sdmc:/3ds/data/Memory3DS/2.png", SF2D_PLACE_RAM);} else {image2 = sfil_load_PNG_file("romfs:/2.png", SF2D_PLACE_RAM);}
	if (FileExists("sdmc:/3ds/data/Memory3DS/3.png")) {image3 = sfil_load_PNG_file("sdmc:/3ds/data/Memory3DS/3.png", SF2D_PLACE_RAM);} else {image3 = sfil_load_PNG_file("romfs:/3.png", SF2D_PLACE_RAM);}
	if (FileExists("sdmc:/3ds/data/Memory3DS/4.png")) {image4 = sfil_load_PNG_file("sdmc:/3ds/data/Memory3DS/4.png", SF2D_PLACE_RAM);} else {image4 = sfil_load_PNG_file("romfs:/4.png", SF2D_PLACE_RAM);}
	if (FileExists("sdmc:/3ds/data/Memory3DS/5.png")) {image5 = sfil_load_PNG_file("sdmc:/3ds/data/Memory3DS/5.png", SF2D_PLACE_RAM);} else {image5 = sfil_load_PNG_file("romfs:/5.png", SF2D_PLACE_RAM);}
	if (FileExists("sdmc:/3ds/data/Memory3DS/6.png")) {image6 = sfil_load_PNG_file("sdmc:/3ds/data/Memory3DS/6.png", SF2D_PLACE_RAM);} else {image6 = sfil_load_PNG_file("romfs:/6.png", SF2D_PLACE_RAM);}
	if (FileExists("sdmc:/3ds/data/Memory3DS/7.png")) {image7 = sfil_load_PNG_file("sdmc:/3ds/data/Memory3DS/7.png", SF2D_PLACE_RAM);} else {image7 = sfil_load_PNG_file("romfs:/7.png", SF2D_PLACE_RAM);}
	if (FileExists("sdmc:/3ds/data/Memory3DS/8.png")) {image8 = sfil_load_PNG_file("sdmc:/3ds/data/Memory3DS/8.png", SF2D_PLACE_RAM);} else {image8 = sfil_load_PNG_file("romfs:/8.png", SF2D_PLACE_RAM);}
	if (FileExists("sdmc:/3ds/data/Memory3DS/9.png")) {image9 = sfil_load_PNG_file("sdmc:/3ds/data/Memory3DS/9.png", SF2D_PLACE_RAM);} else {image9 = sfil_load_PNG_file("romfs:/9.png", SF2D_PLACE_RAM);}
	if (FileExists("sdmc:/3ds/data/Memory3DS/10.png")) {image10 = sfil_load_PNG_file("sdmc:/3ds/data/Memory3DS/10.png", SF2D_PLACE_RAM);} else {image10 = sfil_load_PNG_file("romfs:/10.png", SF2D_PLACE_RAM);}
	backgroundTexture = sfil_load_PNG_file("romfs:/topscreen.png", SF2D_PLACE_RAM);
	font = sftd_load_font_file("romfs:/font.ttf");
}

// free textures
void GUIElementsExit() {
	sf2d_free_texture(backgroundTexture);
	sf2d_free_texture(image0);
	sf2d_free_texture(image1);
	sf2d_free_texture(image2);
	sf2d_free_texture(image3);
	sf2d_free_texture(image4);
	sf2d_free_texture(image5);
	sf2d_free_texture(image6);
	sf2d_free_texture(image7);
	sf2d_free_texture(image8);
	sf2d_free_texture(image9);
	sf2d_free_texture(image10);
	sftd_free_font(font);
}

void DisplayOneCard(int PosX, int PosY, int Content){ 
	if (PosX != 0 && PosY != 0)
	{	
		switch(Content)
		{
			case 0 :
				sf2d_draw_texture(image0, tabPosX[PosX], tabPosY[PosY]);
				break;
			case 1 :
				sf2d_draw_texture(image1, tabPosX[PosX], tabPosY[PosY]);
				break;
			case 2 :
				sf2d_draw_texture(image2, tabPosX[PosX], tabPosY[PosY]);
				break;
			case 3 :
				sf2d_draw_texture(image3, tabPosX[PosX], tabPosY[PosY]);
				break;
			case 4 :
				sf2d_draw_texture(image4, tabPosX[PosX], tabPosY[PosY]);
				break;
			case 5 :
				sf2d_draw_texture(image5, tabPosX[PosX], tabPosY[PosY]);
				break;
			case 6 :
				sf2d_draw_texture(image6, tabPosX[PosX], tabPosY[PosY]);
				break;
			case 7 :
				sf2d_draw_texture(image7, tabPosX[PosX], tabPosY[PosY]);
				break;
			case 8 :
				sf2d_draw_texture(image8, tabPosX[PosX], tabPosY[PosY]);
				break;
			case 9 :
				sf2d_draw_texture(image9, tabPosX[PosX], tabPosY[PosY]);
				break;
			case 10 :
				sf2d_draw_texture(image10, tabPosX[PosX], tabPosY[PosY]);
				break;
			default :
			break;
		}
	}
}

void DisplayCards(int tabDisplay[20]){
	for (int x = 1; x < 6; x++){
		for (int y = 1; y < 5; y++){
			DisplayOneCard(x, y, tabDisplay[4*(x-1)+(y-1)]);
		}
	}

}

void drawScore (int score) {
	sprintf(string, "Score: %i/10", score);
	sftd_draw_textf(font, TEXTXPOS, 90, RGBA8(0, 0, 0, WHITE), SIZE, string);
}

void drawMoves(int attempt) {
	sprintf(string, "Attempt(s): %i", attempt);
	sftd_draw_textf(font, TEXTXPOS, 120, RGBA8(0, 0, 0, WHITE), SIZE, string);

}

void drawTime(u64 timer) {

	if (timer/3600 >= 1) {//if > 59 minutes and 59 seconds
		sftd_draw_textf(font, TEXTXPOS, 150, RGBA8(0, 0, 0, WHITE), SIZE, "Time: 59:59");
	}
	else {
		sprintf(string, "Time: %02llu:%02llu", timer/60, timer-(timer/60)*60);
    	sftd_draw_textf(font, TEXTXPOS, 150, RGBA8(0, 0, 0, WHITE), SIZE, string);
	}
}

//load graphics for the menu
void menu(int PosX, int PosY, int tabDisplay[20], int attempt, u64 timer, int score) {

	// TOP screen
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
	
		sf2d_draw_texture(backgroundTexture, 0, 0);//Display the top screen image

		if (score == 10) {
			sftd_draw_textf(font, TEXTXPOS+5, 180, RGBA8(196, 0, 0, WHITE), 25, "You won!");
		}
 		
 		drawScore(score);
 		drawMoves(attempt);
		drawTime(timer);
		
	sf2d_end_frame();
	
	// BOTTOM screen
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

		DisplayCards(tabDisplay); //Display all the current cards
		
	sf2d_end_frame();	
	sf2d_swapbuffers();
}