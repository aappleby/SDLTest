#include <Windows.h>
#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "Game.h"
#include "Graphics.h"
#include "Input.h"
#include "Util.h"

#pragma comment(lib,"SDL/SDL.lib")
#pragma comment(lib,"SDL/SDLmain.lib")
#pragma comment(lib,"SDL/SDL_image.lib")
#pragma comment(lib,"SDL/SDL_ttf.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

//------------------------------------------------------------------------------
// Main loop

int main(int argc, char **argv)
{
	bool useOpenGL = true;

	int w = 640;
	int h = 480;

	useOpenGL ? InitOpenGL(w,h) : InitSDL(w,h);
	InitTime();
	InitGame(w,h);
	InitInput(w,h);

	while(!g_quit)
	{
		HandleEvents();
		UpdateTime();
		UpdateGame();
		useOpenGL ? DrawOpenGL() : DrawSDL();
	}

	useOpenGL ? ShutdownOpenGL() : ShutdownSDL();

	return 0;
}

//------------------------------------------------------------------------------