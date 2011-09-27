#include "SDL/SDL.h"

#include "Game.h" // for HandleClick

double g_mouseX = 0;
double g_mouseY = 0;

double g_clickX = 0;
double g_clickY = 0;

bool g_quit = false;
bool g_drawText = true;

//------------------------------------------------------------------------------
// User input

void HandleKeyDown(int key)
{
	switch(key)
	{
	case SDLK_ESCAPE:
	case SDLK_q:
		g_quit = true;
		break;

  case SDLK_t:
    g_drawText = !g_drawText;
    break;

	default:
		break;
	}
}

void HandleEvents()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			g_quit = true;
			break;
		
		case SDL_KEYDOWN:
			HandleKeyDown(event.key.keysym.sym);
			break;

		case SDL_MOUSEMOTION:
			g_mouseX = event.button.x;
			g_mouseY = event.button.y;
			break;
			
		case SDL_MOUSEBUTTONDOWN:
			g_clickX = event.button.x;
			g_clickY = event.button.y;

			HandleClick( g_clickX, g_clickY );
			
			break;

		default:
			break;
		}
	}
}


void InitInput ( int screenWidth, int screenHeight )
{
	g_clickX = screenWidth / 2;
	g_clickY = screenHeight / 2;
}