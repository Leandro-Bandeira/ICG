#include <GL/glut.h>

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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,50);
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


int main(int argc, char** argv){

    initWindow(&argc, argv);
    windowInfo();
    /* Diz ao glut qual a função que trata do display
    ou seja, toda vez que mexermos no display, ele chama essa função para atualizar o display */
    glutDisplayFunc(draw);

    glutMainLoop();

    return EXIT_SUCCESS;
}