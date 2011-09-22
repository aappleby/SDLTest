#include <Windows.h>
#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#pragma comment(lib,"SDL/SDL.lib")
#pragma comment(lib,"SDL/SDLmain.lib")
#pragma comment(lib,"SDL/SDL_image.lib")
#pragma comment(lib,"SDL/SDL_ttf.lib")

//------------------------------------------------------------------------------
// Global resources

const int NUM_BUTTONS = 16;
const int BUTTON_SIZE = 64;  //pixels 

SDL_Surface* g_screen = NULL;
SDL_Surface* g_background = NULL; 
SDL_Surface* g_cursor = NULL;
SDL_Surface* g_ball = NULL;
SDL_Surface* g_button0 = NULL;
SDL_Surface* g_button1 = NULL; 

SDL_Rect g_buttons_rect [NUM_BUTTONS];
int g_button_state [NUM_BUTTONS] = {0};

TTF_Font* g_font = NULL;

double g_mouseX = 0;
double g_mouseY = 0;

double g_clickX = 0;
double g_clickY = 0;

double g_ballX = 0;
double g_ballY = 0;

double g_startTime = 0;
double g_time = 0;
double g_delta = 0;
double g_smoothDelta = 0;

bool g_drawText = true;
bool g_quit;

SDL_Surface *load_image_alpha( std::string filename );

//------------------------------------------------------------------------------
// Utility functions

double getTime()
{
	__int64 now;
	__int64 freq;
	
	QueryPerformanceCounter((LARGE_INTEGER*)&now);
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);

	return double(now) / double(freq);
}

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

void toggle_buttons( double x, double y )	
{
	//For each button
	for( int i = 0; i < NUM_BUTTONS; i++ )
	{
		//Is the click on a button?
		if( ( g_clickX > g_buttons_rect[i].x ) && ( g_clickX < g_buttons_rect[i].x + g_buttons_rect[i].w ) && 
			( g_clickY > g_buttons_rect[i].y ) && ( g_clickY < g_buttons_rect[i].y + g_buttons_rect[i].h ) )
		{
			//Change state
			if( g_button_state[i] == 0 )
				g_button_state[i] = 1;
			else
				g_button_state[i] = 0;
		}
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

			toggle_buttons( g_clickX, g_clickY );
			
			break;

		default:
			break;
		}
	}
}

//------------------------------------------------------------------------------
// System initialization & resource loading

SDL_Surface *load_image( std::string filename )
{
	SDL_Surface* loadedImage = IMG_Load( filename.c_str() ); 
	if( loadedImage == NULL ) return NULL;

	SDL_Surface* optimizedImage = SDL_DisplayFormat( loadedImage ); 
	SDL_FreeSurface( loadedImage ); 

	return optimizedImage; 
}

SDL_Surface *load_image_alpha( std::string filename )
{
	SDL_Surface* loadedImage = IMG_Load( filename.c_str() ); 
	if( loadedImage == NULL ) return NULL;

	SDL_Surface* optimizedImage = SDL_DisplayFormatAlpha( loadedImage ); 
	SDL_FreeSurface( loadedImage ); 

	return optimizedImage; 
}

void init_buttons()
{
	//Row1															
	g_buttons_rect[0].x = Sint16( g_screen->w/2 - 2*BUTTON_SIZE );
	g_buttons_rect[0].y = Sint16( g_screen->h/2 - 2*BUTTON_SIZE );
	g_buttons_rect[1].x = Sint16( g_screen->w/2 - BUTTON_SIZE );
	g_buttons_rect[1].y = Sint16( g_screen->h/2 - 2*BUTTON_SIZE );
	g_buttons_rect[2].x = Sint16( g_screen->w/2 );
	g_buttons_rect[2].y = Sint16( g_screen->h/2 - 2*BUTTON_SIZE );
	g_buttons_rect[3].x = Sint16( g_screen->w/2 + BUTTON_SIZE );
	g_buttons_rect[3].y = Sint16( g_screen->h/2 - 2*BUTTON_SIZE );
	//Row2
	g_buttons_rect[4].x = Sint16( g_screen->w/2 - 2*BUTTON_SIZE );
	g_buttons_rect[4].y = Sint16( g_screen->h/2 - BUTTON_SIZE );
	g_buttons_rect[5].x = Sint16( g_screen->w/2 - BUTTON_SIZE );
	g_buttons_rect[5].y = Sint16( g_screen->h/2 - BUTTON_SIZE );
	g_buttons_rect[6].x = Sint16( g_screen->w/2 );
	g_buttons_rect[6].y = Sint16( g_screen->h/2 - BUTTON_SIZE );
	g_buttons_rect[7].x = Sint16( g_screen->w/2 + BUTTON_SIZE );
	g_buttons_rect[7].y = Sint16( g_screen->h/2 - BUTTON_SIZE );
	//Row3
	g_buttons_rect[8].x = Sint16( g_screen->w/2 - 2*BUTTON_SIZE );
	g_buttons_rect[8].y = Sint16( g_screen->h/2 );
	g_buttons_rect[9].x = Sint16( g_screen->w/2 - BUTTON_SIZE );
	g_buttons_rect[9].y = Sint16( g_screen->h/2 );
	g_buttons_rect[10].x = Sint16( g_screen->w/2 );
	g_buttons_rect[10].y = Sint16( g_screen->h/2 );
	g_buttons_rect[11].x = Sint16( g_screen->w/2 + BUTTON_SIZE );
	g_buttons_rect[11].y = Sint16( g_screen->h/2 );
	//Row4
	g_buttons_rect[12].x = Sint16( g_screen->w/2 - 2*BUTTON_SIZE );
	g_buttons_rect[12].y = Sint16( g_screen->h/2 + BUTTON_SIZE );
	g_buttons_rect[13].x = Sint16( g_screen->w/2 - BUTTON_SIZE );
	g_buttons_rect[13].y = Sint16( g_screen->h/2 + BUTTON_SIZE );
	g_buttons_rect[14].x = Sint16( g_screen->w/2 );
	g_buttons_rect[14].y = Sint16( g_screen->h/2 + BUTTON_SIZE );
	g_buttons_rect[15].x = Sint16( g_screen->w/2 + BUTTON_SIZE );
	g_buttons_rect[15].y = Sint16( g_screen->h/2 + BUTTON_SIZE );
}

void Startup()
{
	// set up the screen
	SDL_Init(SDL_INIT_EVERYTHING);
	g_screen = SDL_SetVideoMode( 640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF ); 

	// load our artwork
	g_background = load_image("background.png");
	g_cursor = load_image_alpha("cursor.png");
	g_ball = load_image_alpha("ball.png");
	g_button0 = load_image_alpha("PinkCow.png");
	g_button1 = load_image_alpha("Bull.png");

	// load our fonts
	TTF_Init();
	g_font = TTF_OpenFont("Cursive standard Bold.ttf", 28);

	// store our start time
	g_startTime = getTime();

	// setup buttons
	init_buttons();

	// and do other Windows-specific stuff
	SDL_ShowCursor(false);

	g_clickX = g_screen->w / 2;
	g_clickY = g_screen->h / 2;
}

void Shutdown()
{
	// unload our artwork
	SDL_FreeSurface( g_background );
	SDL_FreeSurface( g_cursor );
	SDL_FreeSurface( g_ball );

	// and shut down SDL
	SDL_Quit();
}

//------------------------------------------------------------------------------
// AI & Animation Code

void Update()
{
	double time = getTime() - g_startTime;
	g_delta = (time - g_time);
	g_smoothDelta = g_smoothDelta * 0.995 + g_delta * 0.005;
	g_time = time;

	// Move the ball towards the click location.
	double speed = 10;
	double dx = (g_clickX - g_ballX) * speed * g_delta;
	double dy = (g_clickY - g_ballY) * speed * g_delta;

	g_ballX += dx;
	g_ballY += dy;
}

//------------------------------------------------------------------------------
// Rendering code

void Draw()
{
	// Clear the screen to the background image

	SDL_BlitSurface( g_background, NULL, g_screen, NULL );

	// Draw the game object

	SDL_Rect obj_rect;

	double wobble = 6;
	double wobbleX = sin(g_time * 4.6) * wobble;
	double wobbleY = sin(g_time * 3.7) * wobble;

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
	  sprintf_s(buf,sizeof(buf),"Hello World - time is %.2f, delta is %.2f", g_time, g_smoothDelta * 1000.0);

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
// Main loop

int main(int argc, char **argv)
{
	Startup();

	while(!g_quit)
	{
		HandleEvents();
		Update();
		Draw();
	}

	Shutdown();

	return 0;
}

//------------------------------------------------------------------------------