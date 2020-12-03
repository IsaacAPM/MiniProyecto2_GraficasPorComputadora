#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void dibuja() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(1.7f);
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Tetera Iluminada");
    glutReshapeFunc(reshape);
    glutDisplayFunc(dibuja);
    // Fondo gris
    glClearColor(0.2, 0.2, 0.2, 1.0);
    // Una fuente de luz para poder ver bien el modelo
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // Atenuación de especular Ks ... sin atenuar es decir maxima reflexión especular
    GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    // Color de la luz ambiente
    GLfloat light0_ambient[] = { 0.8, 0.0, 0.0, 1.0 };
    // Color que difumina el objeto
    GLfloat light0_diffuse[] = { 0.9, 0.9, 0.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light0_specular);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 90);

    // Foco direccional
    GLfloat light1_direction[] = { 10.0, 5.0, 5.0 };
    GLfloat light1_diffuse[] = { 0.0, 0.8, 0.0 };
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 9.0);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

    glEnable(GL_DEPTH_TEST);
    /* posición y orientación */
    gluLookAt(0.0, 0.0, 10.0, /* eye point */
        0.0, 0.0, 0.0,  /* punto de referencia */
        0.0, 1.0, 0.0); /* vector que indica arriba, en este caso Y */
    glutMainLoop();
    return 0;
}