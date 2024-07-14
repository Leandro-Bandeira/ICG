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
  
  /* altere os valores das posições para desenhar a reta */ 
  int x1 = 256;
  int y1 = 256;
  int x2 = 0;
  int y2 = 0;
 
  int *rgbGreen = (int*)malloc(3 * sizeof(int));
  rgbGreen[0] = 0;
  rgbGreen[1] = 255;
  rgbGreen[2] = 0;
  rgbGreen[3] = 255;
  

  t_Pixel pixelInit(x1, y1, rgbGreen);
  t_Pixel pixelEnd(x2,y2, rgbGreen);
  DrawLine(&pixelInit, &pixelEnd);
  
  t_Pixel pixel_i(256, 256, rgbGreen);
  t_Pixel pixel_m(256, 512, rgbGreen);
  t_Pixel pixel_f(512, 256, rgbGreen);
  DrawTriangle(&pixel_i, &pixel_m, &pixel_f);
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

/* Função responsável por desenhar um triangulo na tela 
 * para desenhar um triangulo na tela, basta chamar a função de drawLine
 * do primeiro pixel ao segundo pixel, do segundo ao terceiro e por fim do terceiro ao primeiro */ 
void DrawTriangle(t_Pixel* pixeli, t_Pixel* pixelm, t_Pixel* pixelf){
  
  DrawLine(pixeli, pixelm);
  DrawLine(pixelm, pixelf);
  DrawLine(pixeli, pixelf);

}
