#include "Game.h"

#include "Input.h"
#include "Util.h"

#include "SDL/SDL.h"

SDL_Rect g_buttons_rect [NUM_BUTTONS];
int g_button_state [NUM_BUTTONS] = {0};

double g_ballX = 0;
double g_ballY = 0;

void InitGame( int screenWidth, int screenHeight )
{
	//Row1															
	g_buttons_rect[0].x = Sint16( screenWidth/2 - 2*BUTTON_SIZE );
	g_buttons_rect[0].y = Sint16( screenHeight/2 - 2*BUTTON_SIZE );
	g_buttons_rect[1].x = Sint16( screenWidth/2 - BUTTON_SIZE );
	g_buttons_rect[1].y = Sint16( screenHeight/2 - 2*BUTTON_SIZE );
	g_buttons_rect[2].x = Sint16( screenWidth/2 );
	g_buttons_rect[2].y = Sint16( screenHeight/2 - 2*BUTTON_SIZE );
	g_buttons_rect[3].x = Sint16( screenWidth/2 + BUTTON_SIZE );
	g_buttons_rect[3].y = Sint16( screenHeight/2 - 2*BUTTON_SIZE );
	//Row2
	g_buttons_rect[4].x = Sint16( screenWidth/2 - 2*BUTTON_SIZE );
	g_buttons_rect[4].y = Sint16( screenHeight/2 - BUTTON_SIZE );
	g_buttons_rect[5].x = Sint16( screenWidth/2 - BUTTON_SIZE );
	g_buttons_rect[5].y = Sint16( screenHeight/2 - BUTTON_SIZE );
	g_buttons_rect[6].x = Sint16( screenWidth/2 );
	g_buttons_rect[6].y = Sint16( screenHeight/2 - BUTTON_SIZE );
	g_buttons_rect[7].x = Sint16( screenWidth/2 + BUTTON_SIZE );
	g_buttons_rect[7].y = Sint16( screenHeight/2 - BUTTON_SIZE );
	//Row3
	g_buttons_rect[8].x = Sint16( screenWidth/2 - 2*BUTTON_SIZE );
	g_buttons_rect[8].y = Sint16( screenHeight/2 );
	g_buttons_rect[9].x = Sint16( screenWidth/2 - BUTTON_SIZE );
	g_buttons_rect[9].y = Sint16( screenHeight/2 );
	g_buttons_rect[10].x = Sint16( screenWidth/2 );
	g_buttons_rect[10].y = Sint16( screenHeight/2 );
	g_buttons_rect[11].x = Sint16( screenWidth/2 + BUTTON_SIZE );
	g_buttons_rect[11].y = Sint16( screenHeight/2 );
	//Row4
	g_buttons_rect[12].x = Sint16( screenWidth/2 - 2*BUTTON_SIZE );
	g_buttons_rect[12].y = Sint16( screenHeight/2 + BUTTON_SIZE );
	g_buttons_rect[13].x = Sint16( screenWidth/2 - BUTTON_SIZE );
	g_buttons_rect[13].y = Sint16( screenHeight/2 + BUTTON_SIZE );
	g_buttons_rect[14].x = Sint16( screenWidth/2 );
	g_buttons_rect[14].y = Sint16( screenHeight/2 + BUTTON_SIZE );
	g_buttons_rect[15].x = Sint16( screenWidth/2 + BUTTON_SIZE );
	g_buttons_rect[15].y = Sint16( screenHeight/2 + BUTTON_SIZE );
}

//------------------------------------------------------------------------------

void HandleClick( double clickX, double clickY )
{
	//For each button
	for( int i = 0; i < NUM_BUTTONS; i++ )
	{
		//Is the click on a button?
		if( ( clickX > g_buttons_rect[i].x ) && ( clickX < g_buttons_rect[i].x + BUTTON_SIZE ) && 
			( clickY > g_buttons_rect[i].y ) && ( clickY < g_buttons_rect[i].y + BUTTON_SIZE ) )
		{
			//Change state
			if( g_button_state[i] == 0 )
				g_button_state[i] = 1;
			else
				g_button_state[i] = 0;
		}
	}
}

//------------------------------------------------------------------------------
// AI & Animation Code

void UpdateGame()
{
	// Move the ball towards the click location.
	double speed = 10;
	double dx = (g_clickX - g_ballX) * speed * getDelta();
	double dy = (g_clickY - g_ballY) * speed * getDelta();

	g_ballX += dx;
	g_ballY += dy;
}

//------------------------------------------------------------------------------
