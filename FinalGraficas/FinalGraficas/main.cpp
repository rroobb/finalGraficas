

#include <iostream>
#include <GLUT/glut.h>
#include "Pelota.h"
#include <vector>
//si es windows  <GL/glut.h>
Pelota *aux = new Pelota(0,0,0,0);
int listaPelota, listaFondo;
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glShadeModel (GL_FLAT );

    
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

void display() {
    
    glClear(GL_COLOR_BUFFER_BIT );
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0, 0,0);

    glutWireCube(1);
    glPopMatrix();
  /*  glPushMatrix();
    glTranslatef(aux->getPosX(), aux->getPosY(), aux->getPosZ());
    glScalef(20, 20, 20);
    glCallList(listaPelota);
    glPopMatrix();
    */glutSwapBuffers();
}




void keyboard(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
       
        default:
            break;
    }
    
    
}


void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 0, 6.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, 0, 1.0, 0.0, 6.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(100,myTimer,1);
    
    glutMainLoop();
    return 0;
}