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

Pelota *aux = new Pelota(0,0,0,0,0,0,0);
int listaPelota, listaFondo;

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
    glOrtho(-800, 800, -800, 800, 0, 400);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);
}

void myTimer(int v)
{

    glutPostRedisplay();
    glutTimerFunc(500, myTimer, 1);
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

    glColor3f(0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslatef(0, 0, 0);
    glutWireCube(50);
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
    glutCreateWindow (argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    //glutTimerFunc(5, myTimer, 1);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
