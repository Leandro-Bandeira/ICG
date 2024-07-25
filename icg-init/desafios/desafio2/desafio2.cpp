#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdio>
#include "Structs.h"
#include <math.h>

GLint WINDOW_WIDTH = 500;
GLint WINDOW_HEIGHT = 500;



ConfigData::Structs line;

void initDraw(){
    glColor3f(0.0f, 0.0f, 0.0f);

}
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



void eventos_mouse(GLint buttom, GLint action, GLint x, GLint y){
    if(buttom == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        draw_points(x, y);
        line.incCounterLine();
        if(line.counter_click_line == 1){
            line.set_points_line(x, y, 0);
        }else if(line.counter_click_line == 2){
            line.set_points_line(x, y, 1);
            draw_circle(line);
            line.resetCounterLine();
        }
        
    }
    
    
    
}



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
