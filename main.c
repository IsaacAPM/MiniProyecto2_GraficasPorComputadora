#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glut.h>
#include <stdio.h>

int w = 600, h = 600;
double rx = 0, ry = 0, rz = 0, px = 0, py = 0, pz = 0;

void reshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(GLfloat)h/(GLfloat)w,1,300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init(void){
    glClearColor(0,0,0,0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-10+rx,9+ry,-10+rz,px,py,pz,0,1,0);
    glPushMatrix();

    for(float i=-100;i<100;i+=1.1){
        glColor3f(1.0f,1.0f,1.0f);
        glBegin(GL_LINE_STRIP);
        glVertex3f(i,0,-100);
        glVertex3f(i,0,100);
        glEnd();
    }

    for(float i=-100;i<100;i+=1.1){
        glColor3f(1.0f,1.0f,1.0f);
        glBegin(GL_LINE_STRIP);
        glVertex3f(-100,0,i);
        glVertex3f(100,0,i);
        glEnd();
    }

    //ejes
    //y
    glColor3f(0.0f,1.0f,0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);
    glEnd();
    //x
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);
    glEnd();
    //z
    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
    glEnd();

    //objetos
    glColor3f(1,0,0);
    glutSolidTeapot(1);
    glTranslatef(7,1,0);
    glutSolidTeapot(1);
    glTranslatef(15,0,9);
    glutSolidTeapot(1);
    glTranslatef(-10,0,5);
    glutSolidTeapot(1);
    glPopMatrix();
    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y){
    switch (key)
    {
    case 27: //esc
        exit(0);
        break;
        // eje x
    case 'd':
        rx = rx + 0.2;
        break;
    case 'a':
        rx = rx - 0.2;
        break;
    case 'l':
        px = px + 0.8;
        break;
    case 'j':
        px = px - 0.2;
        break;
        //eje y
    case 'q':
        ry = ry + 0.2;
        break;
    case 'e':
        ry = ry - 0.2;
        break;
    case 'u':
        py = py + 0.8;
        break;
    case 'o':
        py = py - 0.2;
        break;
    case 49: //1
        ry = ry + 0.2;
        py = py + 0.2;
        break;
    case 50: //2
        ry = ry - 0.2;
        py = py - 0.2;
        break;
        // eje z
    case 'w':
        rz = rz + 0.2;
        break;
    case 's':
        rz = rz - 0.2;
        break;
    case 'i':
        pz = pz + 0.8;
        break;
    case 'k':
        pz = pz - 0.8;
        break;
    }
    glutPostRedisplay();
}

void flechas(int key, int x, int y){
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        rx = rx + 0.2;
        px = px - 0.2;
        break;
    case GLUT_KEY_LEFT:
        rx = rx - 0.2;
        px = px - 0.2;
        break;
    case GLUT_KEY_UP:
        rz = rz + 0.2;
        pz = pz + 0.2;
        break;
    case GLUT_KEY_DOWN:
        rz = rz - 0.2;
        pz = pz - 0.2;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,50);
    glutInitWindowSize(w,h);
    glutCreateWindow("Miniproyecto 2");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(flechas);
    glutReshapeFunc(reshape);
    glutMainLoop();
}