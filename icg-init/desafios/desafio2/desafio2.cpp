#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdio>
#include "Structs.h"
#include <math.h>

GLint WINDOW_WIDTH = 500;
GLint WINDOW_HEIGHT = 500;

// Cores do menu
GLfloat r,g,b;
int mode = 0; /* Modo de desenho, 0 para ponto, 1 para linha, 2 para retangulo e 3 circulo */ 
ConfigData::Structs line;

void initDraw(){
    glColor3f(0.0f, 0.0f, 0.0f);

}

/* Altera a cor do ponto */
void change_color_points(int mode){
    /* 0 -> Red, 1-> Green, 2-> Blue*/
    if(mode == 0){
        glColor3f(255.0f, 0.0f, 0.0f);
    }
    else if(mode == 1){
        glColor3f(0.0f, 255.0f, 0.0f);
    }else{
        glColor3f(0.0f, 0.0f, 255.0f);
    }

}
void draw_points(GLint x, GLint y){
   
    /* Define tamanho do pixel */
    glPointSize(3.0); 
    glLineWidth(3.0);
    /* GL_LINE considera apenas pares e GL_LINE_STRIP considera os três*/
    /* O GL_LINE_LOOP conecta todos os vértices */
    /* GL_TRIANGLES constroi um triangulo sólido (preenchido)*/
    
    glBegin(GL_POINTS);
        glVertex2i(x, y);

    glEnd();
    /* Internamente está branco, porém no display ainda não está, devemos dar refresh na tela */
    glFlush();
}


void draw_line(ConfigData::Structs& line){
    /* Define tamanho do pixel */
    glPointSize(3.0); 
    glLineWidth(5.0);
    /* GL_LINE considera apenas pares e GL_LINE_STRIP considera os três*/
    /* O GL_LINE_LOOP conecta todos os vértices */
    /* GL_TRIANGLES constroi um triangulo sólido (preenchido)*/
    
    glBegin(GL_LINES);
        glVertex2i(line.xi_line,line.yi_line);
        glVertex2i(line.xf_line, line.yf_line);

    glEnd();
    /* Internamente está branco, porém no display ainda não está, devemos dar refresh na tela */
    glFlush();
}


void draw_ret(ConfigData::Structs& ret){
    /* Define tamanho do pixel */
    glPointSize(3.0); 
    glLineWidth(5.0);
    /* GL_LINE considera apenas pares e GL_LINE_STRIP considera os três*/
    /* O GL_LINE_LOOP conecta todos os vértices */
    /* GL_TRIANGLES constroi um triangulo sólido (preenchido)*/
  
  glBegin(GL_TRIANGLE_FAN);
        glVertex2i(ret.xi_line,ret.yi_line);
        
        for(int i = 0; i < 2; i++){
          if(i == 0){
            glVertex2i(ret.xi_line, ret.yf_line);
          }else{
            glVertex2i(ret.xf_line, ret.yi_line);
          }
          
          glVertex2i(ret.xf_line, ret.yf_line);
        }
        

    glEnd();
    /* Internamente está branco, porém no display ainda não está, devemos dar refresh na tela */
    glFlush();

}


void draw_circle(ConfigData::Structs& circle){
    glPointSize(3.0); 
    glLineWidth(3.0);
    /* GL_LINE considera apenas pares e GL_LINE_STRIP considera os três*/
    /* O GL_LINE_LOOP conecta todos os vértices */
    /* GL_TRIANGLES constroi um triangulo sólido (preenchido)*/
	    
    int number = 40;
    float twopi = 2 * M_PI;
    float xi = circle.xi_line;
    float yi = circle.yi_line;
    float xf = circle.xf_line;
    float yf = circle.yf_line;

    float radius = sqrt(pow((xf - xi),2) + pow((yf - yi), 2)) + 3.0;
    glBegin(GL_TRIANGLE_FAN);       
    	glVertex2f(xi, yi);
      for(int i = 0; i <= number; i++){
        float theta = (i *twopi) / number;
		    float x = radius* cosf(theta);
        float y = radius* sinf(theta);
        glVertex2f(xi + x,y + yi);
       //glVertex2f((radius)*cosf(i*twopi/number), (radius)*sinf(i*twopi/number));
	    }

    glEnd();
    /* Internamente está branco, porém no display ainda não está, devemos dar refresh na tela */
    glFlush();
}
void initWindow(int* argc, char** argv){

    glutInit(argc, argv);
    int largura_tela = glutGet(GLUT_SCREEN_WIDTH);
    int altura_tela = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition((largura_tela - WINDOW_WIDTH) / 2,(altura_tela - WINDOW_HEIGHT) / 2);
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutCreateWindow("Hello World");
}

void windowInfo(){
    /* A cor que vamos limpar a janela */
    glClearColor(255.0f, 255.0f, 255.0f, 255.0f);  
    /* Define o modo da matriz para tratar transformações */
    glMatrixMode(GL_MODELVIEW);
    /* Define o padrão das posições dos pixels mais a esquerda, mais a direita e cima e baixo */
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0); 
    /* Chama a cor da janela */
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();  
}


/* Verifica se as teclas R,r, G, g, b ou B foram tecladas */
void eventos_teclado(GLubyte key, GLint x, GLint y){
    
    GLint m = glutGetModifiers();

    /* shift conta como capslock*/
    if(key == 'r' or (m == GLUT_ACTIVE_SHIFT && key == 'r')){
        change_color_points(0);
    }
    else if(key == 'g' or (m == GLUT_ACTIVE_SHIFT && key == 'g')){
        change_color_points(1);
    }
    if(key == 'b' or (m == GLUT_ACTIVE_SHIFT && key == 'b')){
        change_color_points(2);
    }
    

}


/* Funçao responsável por gerenciar o sub_menu de desenho */
void handle_menu(GLint menu_index){
   
  switch(menu_index){
    case 0:
      mode = 0;
      break;
    case 1:
      mode = 1;
      break;
    case 2:
      mode = 2;
      break;
    case 3:
      mode = 3;
      break;
  }

  glFlush();
}


/* Gerenciamento do menu prinicipal, caso a opção seja de limpar */ 
void menu_principal(GLint op)
{
  if(op == 1){
    glClearColor(255.0f, 255.0f, 255.0f, 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);

  }

  glFlush();
}
void create_menu(){
  
  /* Criação do sub_menu para desenhar */ 
  GLint submenu_id = glutCreateMenu(handle_menu);
  glutAddMenuEntry("Ponto", 0);
  glutAddMenuEntry("Linha", 1);
  glutAddMenuEntry("Retangulo", 2);
  glutAddMenuEntry("Circulo", 3);
  
  /* Criação do menu principal, onde teremos um outro submenu e uma entrada para limpar */ 
  GLint menu_p = glutCreateMenu(menu_principal);
  glutAddSubMenu("Desenhar", submenu_id);
  glutAddMenuEntry("Limpar", 1);
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);

}

/* Função responsável por detectar o click no mouse
 * e após dois clicks irá desenhar uma linha, retangulo ou circulo, dependendo do modo */
void eventos_mouse(GLint buttom, GLint action, GLint x, GLint y){
    if(buttom == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        
        if(mode == 0){
          draw_points(x, y);
        }
        line.incCounterLine();
        if(line.counter_click_line == 1){
            line.set_points_line(x, y, 0);
        }else if(line.counter_click_line == 2){
            line.set_points_line(x, y, 1);
            if(mode == 1){
              draw_line(line);
            }else if(mode == 2){
              draw_ret(line);
            }else if (mode == 3){

              draw_circle(line);
            }
            line.resetCounterLine();
        }
        
    }
    if(buttom == GLUT_RIGHT_BUTTON && action == GLUT_DOWN){
      create_menu();
    }
    
    
    
}


/* Desenha pontos enquanto o mouse está andando na tela pressionado */
void eventos_mouse_2(GLint x, GLint y){
    draw_points(x,y);  
}



int main(int argc, char** argv){
    
    initWindow(&argc, argv);
    windowInfo();
    /* Callback inicial que irá tratar no display quando iniciar */
    glutDisplayFunc(initDraw);
    glutKeyboardFunc(eventos_teclado);
    glutMouseFunc(eventos_mouse);
    glutMotionFunc(eventos_mouse_2); /* Verifica se o mouse está pressionado e andando */
    glutMainLoop();

    return EXIT_SUCCESS;
}
