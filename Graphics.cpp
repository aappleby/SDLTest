#include "Graphics.h"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "Game.h"
#include "Input.h"
#include "Util.h"

SDL_Surface* g_screen = NULL;
SDL_Surface* g_background = NULL; 
SDL_Surface* g_cursor = NULL;
SDL_Surface* g_ball = NULL;
SDL_Surface* g_button0 = NULL;
SDL_Surface* g_button1 = NULL; 

GLuint h_background = 0;
GLuint h_cursor = 0;
GLuint h_ball = 0;
GLuint h_button0 = 0;
GLuint h_button1 = 0; 

TTF_Font* g_font = NULL;

//------------------------------------------------------------------------------

void InitSDL( int screenWidth, int screenHeight )
{
	// set up the screen
	SDL_Init(SDL_INIT_EVERYTHING);
	g_screen = SDL_SetVideoMode( screenWidth, screenHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF ); 

	// load our artwork
	g_background = LoadImageSDL("background.png");
	g_cursor = LoadImageSDL("cursor.png");
	g_ball = LoadImageSDL("ball.png");
	g_button0 = LoadImageSDL("PinkCow.png");
	g_button1 = LoadImageSDL("Bull.png");

	// load our fonts
	TTF_Init();
	g_font = TTF_OpenFont("Cursive standard Bold.ttf", 28);

	// turn off the mouse cursor
	SDL_ShowCursor(false);
}

void ShutdownSDL()
{
	// unload our artwork
	SDL_FreeSurface( g_background );
	SDL_FreeSurface( g_cursor );
	SDL_FreeSurface( g_ball );

	// and shut down SDL
	SDL_Quit();
}

//------------------------------------------------------------------------------
// Rendering code

void DrawSDL()
{
	// Clear the screen to the background image

	SDL_BlitSurface( g_background, NULL, g_screen, NULL );

	// Draw the game object

	SDL_Rect obj_rect;

	double wobble = 6;
	double wobbleX = sin(getTime() * 4.6) * wobble;
	double wobbleY = sin(getTime() * 3.7) * wobble;

	obj_rect.x = Sint16(g_ballX - g_ball->w/2 + wobbleX);
	obj_rect.y = Sint16(g_ballY - g_ball->h/2 + wobbleY);
	obj_rect.w = 64;
	obj_rect.h = 64;

	SDL_BlitSurface( g_ball, NULL, g_screen, &obj_rect );

	// Draw buttons
	for( int i = 0; i < NUM_BUTTONS; i++ )
	{
		if( g_button_state[i] == 0 )
			SDL_BlitSurface( g_button0, NULL, g_screen, &g_buttons_rect[i] );
		else
			SDL_BlitSurface( g_button1, NULL, g_screen, &g_buttons_rect[i] );
	}

	// Draw the cursor, shifting it a bit so it matches the Windows cursor
	// position

	SDL_Rect cursor_rect;

	cursor_rect.x = Sint16(g_mouseX - 32);
	cursor_rect.y = Sint16(g_mouseY - 25);

	SDL_BlitSurface( g_cursor, NULL, g_screen, &cursor_rect );

	// Draw some text. I'm a little surprised that this "creates" a surface
	// every time you call RenderText(), but I guess it's doing some garbage
	// collection behind the scenes.

  if(g_drawText)
  {
	  char buf[256];
	  sprintf_s(buf,sizeof(buf),"Hello World - time is %.2f, delta is %.2f", getTime(), getSmoothDelta() * 1000.0);

	  SDL_Color textcolor1 = { 0xFF, 0xFF, 0xFF, 0xFF };
	  SDL_Color textcolor2 = { 0x00, 0x00, 0x00, 0x00 };
	  SDL_Surface* text = TTF_RenderText_Blended(g_font, buf, textcolor1);

	  SDL_Rect text_rect;
	  text_rect.x = 10;
	  text_rect.y = 10;
	  SDL_BlitSurface(text, NULL, g_screen, &text_rect);
	  SDL_FreeSurface(text);
  }

	// Drawing done, swap buffers
	SDL_Flip( g_screen ); 
}


//------------------------------------------------------------------------------
// System initialization & resource loading

void InitOpenGL( int screenWidth, int screenHeight )
{
	// set up the screen
	SDL_Init(SDL_INIT_EVERYTHING);
	g_screen = SDL_SetVideoMode( screenWidth, screenHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL ); 

	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);
 
	glViewport(0, 0, screenWidth, screenHeight);
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth, screenHeight, 0, 1, -1);
 
 	// load our artwork

	h_background = LoadImageOpenGL("background.png");
	h_cursor = LoadImageOpenGL("cursor.png");
	h_ball = LoadImageOpenGL("ball.png");
	h_button0 = LoadImageOpenGL("PinkCow.png");
	h_button1 = LoadImageOpenGL("Bull.png");

	// turn off the mouse cursor
	SDL_ShowCursor(false);
}

void ShutdownOpenGL()
{
	// shut down SDL
	SDL_Quit();
}

//------------------------------------------------------------------------------
// Rendering code

void DrawRectOGL( int texid, float x, float y, float w, float h )
{
	glBindTexture(GL_TEXTURE_2D,texid);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
 	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1); glTexCoord2f(0,0); glVertex3f(x + 0, y + 0, 0);
	glColor3f(1, 1, 1); glTexCoord2f(1,0); glVertex3f(x + w, y + 0, 0);
	glColor3f(1, 1, 1); glTexCoord2f(1,1); glVertex3f(x + w, y + h, 0);
	glColor3f(1, 1, 1); glTexCoord2f(0,1); glVertex3f(x + 0, y + h, 0);
	glEnd();
}

void DrawOpenGL()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Clear the screen to the background image
	DrawRectOGL(h_background,0,0,640,480);

	// Draw the game object
	{
		float t = (float)getTime();

		float wobble = 6;
		float wobbleX = sinf(t * 4.6f) * wobble;
		float wobbleY = sinf(t * 3.7f) * wobble;

		float w = 48;
		float h = 48;
		float x = g_ballX - w/2 + wobbleX;
		float y = g_ballY - h/2 + wobbleY;

		DrawRectOGL(h_ball,x,y,w,h);
	}

	// Draw buttons
	for( int i = 0; i < NUM_BUTTONS; i++ )
	{
		if( g_button_state[i] == 0 )
			DrawRectOGL( h_button0, g_buttons_rect[i].x, g_buttons_rect[i].y, BUTTON_SIZE, BUTTON_SIZE );
		else
			DrawRectOGL( h_button1, g_buttons_rect[i].x, g_buttons_rect[i].y, BUTTON_SIZE, BUTTON_SIZE );
	}

	// Draw the cursor, shifting it a bit so it matches the Windows cursor
	// position

	DrawRectOGL(h_cursor,g_mouseX-32,g_mouseY-25,100,100);

	// Draw some text. I'm a little surprised that this "creates" a surface
	// every time you call RenderText(), but I guess it's doing some garbage
	// collection behind the scenes.

	/*
	if(g_drawText)
	{
		char buf[256];
		sprintf_s(buf,sizeof(buf),"Hello World - time is %.2f, delta is %.2f", getTime(), getSmoothDelta() * 1000.0);

		SDL_Color textcolor1 = { 0xFF, 0xFF, 0xFF, 0xFF };
		SDL_Color textcolor2 = { 0x00, 0x00, 0x00, 0x00 };
		SDL_Surface* text = TTF_RenderText_Blended(g_font, buf, textcolor1);

		SDL_Rect text_rect;
		text_rect.x = 10;
		text_rect.y = 10;
		SDL_BlitSurface(text, NULL, g_screen, &text_rect);
		SDL_FreeSurface(text);
	}
	*/

	SDL_GL_SwapBuffers();
}

//------------------------------------------------------------------------------
