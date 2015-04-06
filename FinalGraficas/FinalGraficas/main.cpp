// Smash Junk Food
// Roberto Rivera - A00618181
// Marialicia Villarreal - A00811095

#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include "Pelota.h"
#include <vector>

using namespace std;

Pelota *aux = new Pelota(0,0,0,0);
int listaPelota, listaFondo;

const float medida = 1.0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(60.0, 1.0, 1.0, 10.0);
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 3.5);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 2.0, 0, 0, 0, 0, 1, 0);
}

void myTimer(int v)
{
    glutPostRedisplay();
    glutTimerFunc(5, myTimer, 1);
}

void createList()
{
    listaPelota= glGenLists(1);
    glNewList(listaPelota, GL_COMPILE);
    glutSolidSphere(1, 1,10);
    glLineWidth(10);
    glEndList();
    listaFondo= glGenLists(1);
    glNewList(listaFondo, GL_COMPILE);
    glBegin(GL_QUADS);
    glVertex3f( -.5, -.5, 2 );
    glVertex3f( -.5,  .5, 2);
    glVertex3f(  .5,  .5, 2 );
    glVertex3f(  .5, -.5, 2 );
    glEnd();
    glLineWidth(10);
    glEndList();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(1.0, 1.0, 1.0, 0.0);

    glBegin(GL_QUADS);

    //Arriba (amarillo)
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f( -medida, medida, -medida );
    glVertex3f(  medida, medida, -medida );
    glVertex3f(  medida, medida,  medida );
    glVertex3f( -medida, medida,  medida );

    glColor3f(1.0, 1.0, 1.0);
    //Atrás (blanco)
    glVertex3f( -medida, -medida, -medida );
    glVertex3f(  medida, -medida, -medida );
    glVertex3f(  medida,  medida, -medida );
    glVertex3f( -medida,  medida, -medida );

    //Derecha (verde)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f( medida, -medida, -medida );
    glVertex3f( medida,  medida, -medida );
    glVertex3f( medida,  medida,  medida );
    glVertex3f( medida, -medida,  medida );

    //Izquierda (azul)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f( -medida, -medida, -medida );
    glVertex3f( -medida, -medida,  medida );
    glVertex3f( -medida,  medida,  medida );
    glVertex3f( -medida,  medida, -medida );

    //Abajo (magenta)
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f( -medida, -medida, -medida );
    glVertex3f(  medida, -medida, -medida );
    glVertex3f(  medida, -medida,  medida );
    glVertex3f( -medida, -medida,  medida );

    glEnd();

    glPopMatrix();


    glColor3ub(0, 0, 0);
    glPushMatrix();
    glScalef (0.5, 0.5, 1.0);
    glTranslatef (0.5, 0.0, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    glutSwapBuffers();
}


void keyboard(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
        case 27: exit(0); break;
        default:
            break;
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize (800,800);
    glutInitWindowPosition (0,0);
    glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB| GLUT_DEPTH);
    glutCreateWindow("Smash Junk Food");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(500, myTimer, 1);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
