#include <sf2d.h>
#include <sftd.h>
#include <sfil.h>
#include <string.h>

// Colors
#define BLACK RGBA8(0, 0, 0, 255)
#define RED RGBA8(255, 0, 0, 255)
#define WHITE RGBA8(255, 255, 255, 255)

#define SIZE 20 //Font size
#define TEXTXPOS 40 //Text X position with left texts

// screens width
#define BOTTOM 320
#define TOP 400

bool FileExists(const char *filename);
void DisplayOneCard(int PosX, int PosY, int Content);
void DisplayCards(int tabDisplay[20]);
void GUIElementsInit();
void GUIElementsExit();
void drawScore (int score);
void drawTime(u64 timer);
void drawMoves(int attempt);
void menu(int PosX, int PosY, int tabDisplay[20], int attempt, u64 timer, int score);