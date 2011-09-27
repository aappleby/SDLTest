/*
HDC    hdc;  // A TrueType font has already been selected  
HGLRC  hglrc; 
GLYPHMETRICSFLOAT agmf[256]; 
 
// Make hglrc the calling thread's current rendering context  
wglMakeCurrent(hdc, hglrc); 
 
// create display lists for glyphs 0 through 255 with 0.1 extrusion  
// and default deviation. The display list numbering starts at 1000  
// (it could be any number)  
wglUseFontOutlines(hdc, 0, 255, 1000, 0.0f, 0.1f,  
            WGL_FONT_POLYGONS, &agmf); 
 
// Set up transformation to draw the string  
glLoadIdentity(); 
glTranslate(0.0f, 0.0f, -5.0f) 
glScalef(2.0f, 2.0f, 2.0f); 
 
// Display a string  
glListBase(1000); // Indicates the start of display lists for the glyphs  
// Draw the characters in a string  
glCallLists(24, GL_UNSIGNED_BYTE, "Hello Windows OpenGL World.");
*/


/*
 LOGFONT     lf;
   HFONT       hFont, hOldFont;
   GLYPHMETRICSFLOAT agmf[256];

   // An hDC and an hRC have already been created.
   wglMakeCurrent( hDC, hRC );

   // Let's create a TrueType font to display.
   memset(&lf,0,sizeof(LOGFONT));
   lf.lfHeight               =   -20 ;
   lf.lfWeight               =   FW_NORMAL ;
   lf.lfCharSet              =   ANSI_CHARSET ;
   lf.lfOutPrecision         =   OUT_DEFAULT_PRECIS ;
   lf.lfClipPrecision        =   CLIP_DEFAULT_PRECIS ;
   lf.lfQuality              =   DEFAULT_QUALITY ;
   lf.lfPitchAndFamily       =   FF_DONTCARE|DEFAULT_PITCH;
   lstrcpy (lf.lfFaceName, "Arial") ;

   hFont = CreateFontIndirect(&lf);
   hOldFont = SelectObject(hDC,hFont);

   // Create a set of display lists based on the TT font we selected
   if (!(wglUseFontOutlines(hDC, 0, 255, GLF_START_LIST, 0.0f, 0.15f,
      WGL_FONT_POLYGONS, agmf)))
        MessageBox(hWnd,"wglUseFontOutlines failed!","GLFont",MB_OK);

   DeleteObject(SelectObject(hDC,hOldFont));
*/

/*
 // Display string with display lists created by wglUseFontOutlines()
   glListBase(GLF_START_LIST); // indicate start of display lists

   // Draw the characters
   glCallLists(6, GL_UNSIGNED_BYTE, "OpenGL");
*/