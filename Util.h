#pragma once

#include <string>

struct SDL_Surface;

void InitTime();
void UpdateTime();

double getTime();
double getDelta();
double getSmoothDelta();

SDL_Surface* LoadImageSDL   ( std::string filename );
int          LoadImageOpenGL( std::string filename );