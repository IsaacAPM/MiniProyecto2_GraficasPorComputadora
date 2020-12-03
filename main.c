#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glut.h>
#include <stdio.h>

int w = 600, h = 600;
double rx = 0, ry = 0, rz = 0, px = 0, py = 0, pz = 0;

void setMaterial(GLfloat ambientR,GLfloat ambientG,GLfloat ambientB,
                 GLfloat diffuseR,GLfloat diffuseG,GLfloat diffuseB,
                 GLfloat specularR,GLfloat specularG,GLfloat specularB, GLfloat shininess){
    
    GLfloat ambient[] = { ambientR, ambientG, ambientB };
    GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
    GLfloat specular[] = { specularR, specularG, specularB };
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shininess);
}

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
    glViewport(0,0,h,w);
    glPushMatrix();
    setMaterial(0,0.1,0,0.1,0.1,0.1,0.0,0.9,0.0,1);
    glutSolidSphere(1,20,20);
    glPopMatrix();

    glPushMatrix();
    setMaterial(0.1,0,0,0.1,0.1,0.1,0.9,0.0,0.0,1);
    glTranslated(2,0,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    setMaterial(0,0,0,0.1,0.1,0.1,0.5,0.5,0.5,1);
    glTranslated(0,0,2);
    glutSolidTeapot(1);
    glPopMatrix();

    glPopMatrix();
    glPushMatrix();
    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y){
    switch (key)
    {
    case 27: //esc
        exit(0);
        break;
        // eje x
    case 'q':
        rx = rx + 0.2;
        break;
    case 'w':
        rx = rx - 0.2;
        break;
    case 'e':
        px = px + 0.8;
        break;
    case 'r':
        px = px - 0.2;
        break;
        //eje y
    case 'a':
        ry = ry + 0.2;
        break;
    case 's':
        ry = ry - 0.2;
        break;
    case 'd':
        py = py + 0.8;
        break;
    case 'f':
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
    case 'z':
        rz = rz + 0.2;
        break;
    case 'x':
        rz = rz - 0.2;
        break;
    case 'c':
        pz = pz + 0.8;
        break;
    case 'v':
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

    //Color de fondo
    glClearColor(0.125,0.69,0.67, 1.0);

    //Codigo de iluminación general

    GLfloat light_ambient[] = {0.0,0.0,0.0,1.0};
    GLfloat light_specular[] = {1.0,1.0,1.0,1.0};
    GLfloat light_diffuse[] = {1.0,1.0,1.0,1.0};
    GLfloat light_position[] = {1.0,1.0,1.0,1.0};

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light_ambient);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40,1,4,20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);

    glutMainLoop();
}