#include <GL/glut.h>
#include <cstdio>
GLint WINDOW_WIDTH = 500;
GLint WINDOW_HEIGHT = 500;

void draw(){
    /* Chama a cor da janela */
    glClear(GL_COLOR_BUFFER_BIT);

    /* define a cor do pixel */
    glColor3f(1.0f,0.0f,0.0f);
    /* Define tamanho do pixel */
    glPointSize(3.0); 
    glLineWidth(3.0);
    /* GL_LINE considera apenas pares e GL_LINE_STRIP considera os três*/
    /* O GL_LINE_LOOP conecta todos os vértices */
    /* GL_TRIANGLES constroi um triangulo sólido (preenchido)*/
    
    glBegin(GL_TRIANGLES);
        glVertex2i(250, 100);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex2i(100, 400);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex2i(400, 400);


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
}


/* tecla e posição x e y do mouse */
void eventos_teclado(GLubyte key, GLint x, GLint y){
    printf("Evento do teclado disparado\n");

}

void eventos_especiais_teclado(GLint key, GLint x, GLint y){
    printf("Eventos do teclado especial\n");
}

void eventos_mouse(GLint buttom, GLint action, GLint x, GLint y){
    if(buttom == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        printf("Bota esquerdo pressionado na posição (%d, %d)\n", x , y);   
        
    }
    
    else if(buttom == GLUT_LEFT_BUTTON && action == GLUT_UP){
        printf("Botao esquerdo liberado na posicao (%d, %d)\n", x, y);
    }
    else if(buttom == GLUT_RIGHT_BUTTON && action == GLUT_DOWN){
        printf("Bota direito pressionado na posição (%d, %d)\n", x , y);   
    }else if(buttom == GLUT_RIGHT_BUTTON  && action == GLUT_UP){
        printf("Botao direito liberado na posicao (%d, %d)\n", x, y);
    }
    
}

void eventos_mouse_2(GLint x, GLint y){
    printf("movendo na posição (%d, %d)\n", x , y);  
}
int main(int argc, char** argv){

    initWindow(&argc, argv);
    windowInfo();
    /* callback inicial com a incialização do display */
    glutDisplayFunc(draw);
    glutKeyboardFunc(eventos_teclado);
    glutSpecialFunc(eventos_especiais_teclado); /* Pega as teclas funcionais do teclado */
    glutMouseFunc(eventos_mouse);
    glutPassiveMotionFunc(eventos_mouse_2);
    glutMainLoop();

    return EXIT_SUCCESS;
}