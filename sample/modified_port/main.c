#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>
#include "graphics.h"

// tab that contains coordinates (touchscreen)
int tabTouchX[320] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int tabTouchY[240] = {1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0, 0, 0, 0, 0, 2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,0, 0, 0, 0, 0, 3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,3 ,0, 0, 0, 0, 0, 4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,0};

//tab of answers
int tabAnwser[20] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10};

//Tab displayed
int tabDisplay[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//Variables
touchPosition touch;
int PosX = 0; 
int PosY = 0;
int PosX2 = 0;
int PosY2 = 0;
bool touchactive = true; //if we are allowed to touch the screen
int nb = 0; //number of returned cards
int score = 0; //Score of the game. if score == 10, you win (all 10 pairs returned)
int timecount = 0; //just a time counter 
int attempt = 0;
u64 totalsecondsatstart = 0; //total of seconds at start
u64 totalsecondstomemorize = 0;
u64 currenttime = 0; //current total seconds
bool midnightpassed = false; //to fix a bug when time = 23h59-> 00h00, because time<totalsecondsatstart
bool waitXsecondsisactive = false;
// Audio variables
u8* buffer;
u32 size;

// Audio functions (load audio)
void audio_load(const char *audio){
   /* FILE *file = fopen(audio, "rb");
    fseek(file, 0, SEEK_END);// seek to end of file
    off_t size = ftell(file);// file pointer tells us the size
    fseek(file, 0, SEEK_SET);// seek back to start
    buffer = linearAlloc(size);//allocate a buffer
    off_t bytesRead = fread(buffer, 1, size, file);//read contents!
    fclose(file);//close the file because we like being nice and tidy
    csndPlaySound(8, SOUND_FORMAT_16BIT | SOUND_REPEAT, 44100, 1, 0, buffer, buffer, size);
    linearFree(buffer);/*
}

// Audio functions (stop audio)
void audio_stop(void){
    /*csndExecCmds(true);
    CSND_SetPlayState(0x8, 0);
    memset(buffer, 0, size);
    GSPGPU_FlushDataCache(buffer, size);
    linearFree(buffer);*/
}
	
void exitServices() {
	/*audio_stop();
	audio_stop();
	csndExit();*/
	GUIElementsExit();
	romfsExit();
	sftd_fini();
	sf2d_fini();
}

void initServices() {
	sf2d_init();
	sf2d_set_clear_color(WHITE);
	sf2d_set_vblank_wait(1);
	sftd_init();
	romfsInit();
	GUIElementsInit();
	/*csndInit();*/
	srand(osGetTime());
}

void RandomizationOfThetabAnwser(){
	int max, rand1, rand2, mem = 0;

	for (max = 0; max <200; max++){
		rand1 = rand()%20; //Random between 0 and 19
		rand2 = rand()%20;
		mem = tabAnwser[rand1];
		tabAnwser[rand1] = tabAnwser[rand2];
		tabAnwser[rand2] = mem;
	}
}

u64 CalculateCurrentTotalSeconds() {
	u64 theTime = osGetTime();
	//u64 miliseconds = ((theTime / 1000) % 86400) % 10;
    u64 seconds = ((theTime / 1000) % 86400) % 60;
    u64 minutes = (((theTime / 1000) % 86400) % 3600) / 60;
    u64 hours = ((theTime / 1000) % 86400) / 3600;
    if (seconds+60*minutes+3600*hours == 0) {
    	midnightpassed = true;
    }
    if (midnightpassed) {
    	return (216000+seconds+60*minutes+3600*hours);//216000=24hours in seconds
    }
    else {
    	return (seconds+60*minutes+3600*hours);
    }
}

bool waitXseconds (int seconds) { //return true after x seconds passed
	if (waitXsecondsisactive){
		if (currenttime-totalsecondstomemorize >= seconds) {
			waitXsecondsisactive = false;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		totalsecondstomemorize = CalculateCurrentTotalSeconds();
		waitXsecondsisactive = true;
		return false;
	}
}


int main() {
	initServices();
	//Audio load
	/*FILE *fp = fopen ("sdmc:/3ds/data/Memory3DS/music.raw", "r");
	if (fp!=NULL) {
		fclose (fp);
		audio_load("sdmc:/3ds/data/Memory3DS/music.raw");}
	else {audio_load("romfs:/music.raw");}*/
	
	RandomizationOfThetabAnwser();
	totalsecondsatstart = CalculateCurrentTotalSeconds();

	// Main loop
	while (aptMainLoop() && !(hidKeysDown() & KEY_START)) { //If start is pressed, exit
		hidScanInput();
		u32 kDown = hidKeysDown();
		hidTouchRead(&touch);

		if (nb == 2){ //If two cards returned 
			if (tabDisplay[4*(PosX-1)+(PosY-1)] == tabDisplay[4*(PosX2-1)+(PosY2-1)]) { //If the two returned cards are the same pair
				score++;
				nb = 0;
				touchactive = true;
			}
			else {
				if (waitXseconds(2)) { //Not precise....
					tabDisplay[4*(PosX-1)+(PosY-1)] = 0; //We return the cards to 0, back
					tabDisplay[4*(PosX2-1)+(PosY2-1)] = 0;
					timecount = 0;//reset the counter
					nb = 0;
					attempt++;
					touchactive = true;
				}
			}
		}

		if (kDown & KEY_TOUCH && touchactive) //if we touch the bottom screen and we are allowed to
		{	
			if (nb == 0){ //If 0 card returned
				if (tabTouchX[touch.px] != 0 && tabTouchY[touch.py] != 0) { //If the card exists
					PosX = tabTouchX[touch.px];
					PosY = tabTouchY[touch.py];
					if (tabDisplay[4*(PosX-1)+(PosY-1)] == 0) {//if selected card is equal to 0, back.
						tabDisplay[4*(PosX-1)+(PosY-1)] = tabAnwser[4*(PosX-1)+(PosY-1)];
						PosX2 = PosX; //Save the card position, will usefull when comparing two cards, later
						PosY2 = PosY;
						nb = 1; //one card returned
					}
				}
			}

			if (nb == 1){ //If one card already returned
				if (tabTouchX[touch.px] != 0 && tabTouchY[touch.py] != 0) { //If the card exists
					PosX = tabTouchX[touch.px];
					PosY = tabTouchY[touch.py];
					if (PosX != PosX2 || PosY != PosY2) { //If you doesn't touch the same previous card
						if (tabDisplay[4*(PosX-1)+(PosY-1)] == 0) { //if selected cards is equal to 0, back.
							tabDisplay[4*(PosX-1)+(PosY-1)] = tabAnwser[4*(PosX-1)+(PosY-1)];
							nb = 2; //two card returned
							touchactive = false; //We can't touch the screen
						}
					}
				}
			}
		}

		if (hidKeysDown() & KEY_SELECT && touchactive) { //Reset the game.
			nb = 0;
			score = 0;
			attempt = 0;
			for (int x = 0; x < 20; x++){ //return all cards to 0, back
				tabDisplay[x] = 0;
			}
			RandomizationOfThetabAnwser();
			totalsecondsatstart = CalculateCurrentTotalSeconds();
		}

		if (score != 10) {//if the player haven't won yet
			currenttime = CalculateCurrentTotalSeconds();
		}

		// menu is printed in this function
		menu(PosX, PosY, tabDisplay, attempt, currenttime-totalsecondsatstart, score); //currenttime-totalsecondsatstart ## Problems with 23h59 -> 00h00
	}

	// closing every open services and free pointers, to avoid system crashes
	exitServices();
	return 0;
}
