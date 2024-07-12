#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define IMAGE_WIDTH  512 // número de colunas da imagem.
#define IMAGE_HEIGHT 512 // número de linhas da imagem.

unsigned char * FBptr;


struct t_Pixel{
  int m_x;
  int m_y;
  int* m_rgb;
  t_Pixel(int x, int y, int* rgb){
    m_x = x;
    m_y = y;
    m_rgb = rgb;
  }
};
#endif // _DEFINITIONS_H_
