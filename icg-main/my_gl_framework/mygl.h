#ifndef _MYGL_H_
#define _MYGL_H_
#endif

#include "definitions.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void);

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

void DrawTriangle(t_Pixel* pixeli, t_Pixel* pixelm, t_Pixel* pixelf);
void PutPixel(t_Pixel* pixel);
void DrawLine(t_Pixel* pixeli, t_Pixel* pixelf);
