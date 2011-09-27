#include "Util.h"

#include <Windows.h>
#include <assert.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

double g_startTime = 0;
double g_time = 0;
double g_delta = 0;
double g_smoothDelta = 0;

//------------------------------------------------------------------------------
// Utility functions

double getWallTime()
{
	__int64 now;
	__int64 freq;
	
	QueryPerformanceCounter((LARGE_INTEGER*)&now);
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);

	return double(now) / double(freq);
}

void InitTime()
{
	g_startTime = getWallTime();
}

void UpdateTime()
{
	double time = getWallTime() - g_startTime;
	g_delta = (time - g_time);
	g_smoothDelta = g_smoothDelta * 0.995f + g_delta * 0.005f;
	g_time = time;
}

double getTime()
{
	return g_time;
}

double getDelta()
{
	return g_delta;
}

double getSmoothDelta()
{
	return g_smoothDelta;
}

//------------------------------------------------------------------------------

SDL_Surface *LoadImageSDL( std::string filename )
{
	SDL_Surface* loadedImage = IMG_Load( filename.c_str() ); 
	if( loadedImage == NULL ) return NULL;

	SDL_Surface* optimizedImage = SDL_DisplayFormatAlpha( loadedImage ); 
	SDL_FreeSurface( loadedImage ); 

	return optimizedImage; 
}

//------------------------------------------------------------------------------

int LoadImageOpenGL( std::string filename )
{
	// Load the image using SDL
	SDL_Surface* img = IMG_Load(filename.c_str());
	assert(img);
	if(img == NULL) return 0;

	// Remember which texture OpenGL had loaded before we go changing it
	GLint old_texture = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D,&old_texture);

	// Create a new texture object and bind it
	GLuint id = 0;
	glGenTextures(1,&id);
	glBindTexture(GL_TEXTURE_2D,id);

	// Set default options for the texture object
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	// and load the SDL_Surface image data into it
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,img->w,img->h,GL_RGBA,GL_UNSIGNED_BYTE,img->pixels);

	// then ditch the SDL_Surface
	SDL_FreeSurface(img);

	// and restore the old texture binding
	glBindTexture(GL_TEXTURE_BINDING_2D,old_texture);

	// and we're done
	return (int)id;
}

//------------------------------------------------------------------------------
