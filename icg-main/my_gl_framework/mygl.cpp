#include "definitions.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <chrono>
#include <thread>



using namespace std;

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
    //*************************************************************************
    // Chame aqui as funções do mygl.h
    //*************************************************************************
  int *rgbGreen = (int*)malloc(3 * sizeof(int));
  rgbGreen[0] = 0;
  rgbGreen[1] = 255;
  rgbGreen[2] = 0;
  rgbGreen[3] = 255;
   
  t_Pixel pixelInit(10, 20, rgbGreen);


  t_Pixel pixelEnd(511,511, rgbGreen);

  DrawLine(&pixelInit, &pixelEnd);

}


/* Temos que ter em mente, que a nossa tela tem as dimensões 512x512
 * logo temos um total de 512x512=262144 bytes, se temos a posição (x,y)
  * sua posição inicial no color buff será dada por (x*4* + y * IMAGE_WIDTH 4) 
  * Nessa logica o x está na horizontal e o y na vertical (coluna x linha)*/  
void PutPixel(t_Pixel* pixel) {
    const int i = (pixel->m_x * 4) + (pixel->m_y * 4 * IMAGE_WIDTH);
    FBptr[i] = pixel->m_rgb[0];
    FBptr[i + 1] = pixel->m_rgb[1];
    FBptr[i + 2] = pixel->m_rgb[2];
    FBptr[i + 3] = pixel->m_rgb[3];
}
  
void DrawLine(t_Pixel* pixel_i, t_Pixel* pixel_f)
{
  /* Configurações da cor da reta */ 
  int* rgb = pixel_i->m_rgb;

  int dy = pixel_f->m_y - pixel_i->m_y;
  int dx = pixel_f->m_x - pixel_i->m_x;
  int x = pixel_i->m_x;
  int y = pixel_i->m_y;
  int e = 0;
  
  /* Caso em que os pixels estão na mesma linha, mas colunas diferentes */ 
  if(pixel_i->m_y == pixel_f->m_y){
    while(x != pixel_f->m_x){
      t_Pixel pixel(x,y,rgb);
      PutPixel(&pixel);
      x = pixel_i->m_x <= pixel_f->m_x ? x + 1 : x - 1;  
    }
  }
  /* Caso em que os pixels estão na mesma coluna, mas linhas diferentes */ 
  else if(pixel_i->m_x == pixel_f->m_x){
    while(y != pixel_f->m_y){
      t_Pixel pixel(x,y,rgb);
      PutPixel(&pixel);
      y = (pixel_i->m_y <= pixel_f->m_y) ? y + 1 : y - 1;
    }
  }
  else{
    while (x != pixel_f->m_x){
      t_Pixel pixel(x, y, rgb);
      PutPixel(&pixel);
      x = pixel_f->m_x >= pixel_i->m_x ? x + 1:x-1;
      e += 2 * abs(dy);
      if (e >= abs(dx) ){
        y = pixel_f->m_y >= pixel_i->m_y ? y + 1 : y -1; 
        e -= 2*abs(dx);
      }
    }
  }
  
}
