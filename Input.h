#pragma once

extern double g_mouseX;
extern double g_mouseY;

extern double g_clickX;
extern double g_clickY;

extern bool g_quit;
extern bool g_drawText;

void InitInput( int screenWidth, int screenHeight );
void HandleEvents();