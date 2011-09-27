#pragma once

// Game state

const int NUM_BUTTONS = 16;
const int BUTTON_SIZE = 64;  //pixels 

struct SDL_Rect;
extern SDL_Rect g_buttons_rect[];
extern int g_button_state[];

extern double g_ballX;
extern double g_ballY;

// Game functions

void InitGame( int screenWidth, int screenHeight );
void HandleClick( double clickX, double clickY );
void UpdateGame();