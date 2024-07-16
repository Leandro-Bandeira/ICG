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
     
  
  /* Criando cores para desenhar as retas e os triangulos */
  int *rgbGreen = (int*)malloc(3 * sizeof(int));
  rgbGreen[0] = 0;
  rgbGreen[1] = 255;
  rgbGreen[2] = 0;
  rgbGreen[3] = 255;
  
  int *rgbBlue = (int*)malloc(3* sizeof(int));
  rgbBlue[0] = 0;
  rgbBlue[1] = 0;
  rgbBlue[2] =  255;
  rgbBlue[3] = 255;
  
  /* Desenhando em cada octeto */

  /* Desenhando inicialmente do centro para a direita */ 
  t_Pixel pixelInit(256, 256, rgbGreen);
  t_Pixel pixelEnd(511,256, rgbGreen);
  DrawLine(&pixelInit, &pixelEnd);

  int x1 =  0;
  int y1 = 0;

  /* o For abaixo é responsável por desenhar as linhas por todo o octeto */
  for(int i = 1; i < 8; i++){
    if (i == 1){
      x1 = 511;
      y1 = 0;
    }else if(i == 2){
      x1 = 256;
      y1 = 0;
    }else if(i == 3){
      x1 = 0;
      y1 = 0;
    }else if(i == 4){
      x1 = 0;
      y1 = 256;
    }else if(i == 5){
      x1 = 0;
      y1 = 511;
    }else if (i == 6){
      x1 = 256;
      y1 = 511;
    }else{
      x1 = y1 = 511;
    }
    t_Pixel pixelEnd(x1,y1, rgbGreen);
    DrawLine(&pixelInit, &pixelEnd);
  }
  t_Pixel pixel_i(100, 100, rgbBlue);
  t_Pixel pixel_m(100, 300, rgbBlue);
  t_Pixel pixel_f(300, 350, rgbBlue);
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
  
  /* Como o ponto está generalizado para qualquer posição do plano
   * devemos pegar a diferença absoluta tanto em dx como em dy,
   * porem em dy vamos pegar sempre o negativo */
  int dy = -abs(pixel_f->m_y - pixel_i->m_y);
  int dx = abs(pixel_f->m_x - pixel_i->m_x);
  int x = pixel_i->m_x;
  int y = pixel_i->m_y;
  int e = dx + dy;

 /* O loop abaixo está generalizado para quer ponto x e y no plano cartesiano
  * só vamos parar o loop, caso as posições de x e y estejam exatamente iguais
  * a suas posições finais.*/ 
  while (1){
    t_Pixel pixel(x, y, rgb);
    PutPixel(&pixel);
      
    if(x == pixel_f->m_x and y == pixel_f->m_y){
      break;
    }
    /* Dobramos o errado para uma variável e2 */
    int e2 = 2 * e;
    /* Caso a variação de y, seja menor ou igual a e2, iremos mudar a posição de x
     * caso o final seja maior, iremos somar caso não iremos subtrair */
    if (e2 >= dy){
      if (pixel_f->m_x == x){
        break;
      }
      e += dy;
     
      x = (pixel_i->m_x < pixel_f->m_x ? x+ 1 :x-1);
    }
    /* Nesse caso, fazemos o equivalente porem para y */
    if (e2 <= dx){
      if(pixel_f->m_y == y){
        break;
      }
      e += dx;

      y = (pixel_i->m_y < pixel_f->m_y ? y+ 1 :y-1);
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
