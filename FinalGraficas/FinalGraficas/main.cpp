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

Pelota *actual = new  Pelota(0,0,4,0);
int listaPelota, listaFondo;
float velX,velY;
bool isMoving = false;
vector<Pelota*> pelotasEstaticas;

const float medida = 10.0;

void initValues(){
    velX = 0;
    velY = 0;
    isMoving = false;
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    initValues();
}

void reshape (int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 1.0f, -6.0f);
}

void myTimer(int v)
{
    if (isMoving) {

        if (actual->getPosX()>=9 || actual->getPosX()<=-9) {
            velX*=-1;
        }
        if (actual->getPosY()>=9 || actual->getPosY()<=-9) {
            velY*=-1;
        }
        if (actual->getPosZ()<=-60) {
            initValues();
            pelotasEstaticas.push_back(actual);
            actual = new Pelota(0,0,4,0);
            glutPostRedisplay();
            return;
        }
        for (int i = 0; i<pelotasEstaticas.size() && i >=0; i++) {
            switch (pelotasEstaticas[i]->checarColision(*actual)) {
                case 0:
                    break;
                case 1:
                    initValues();
                    pelotasEstaticas.push_back(actual);
                    actual = new Pelota(0,0,4,0);
                    glutPostRedisplay();
                    return;
                case 3:
                    initValues();
                    actual->destruir();
                    pelotasEstaticas[i]->destruir();
                    pelotasEstaticas[i]->getColision()->destruir();
                    for (int cont=0; cont<pelotasEstaticas.size(); cont++) {
                        if (pelotasEstaticas[cont] == pelotasEstaticas[i]->getColision()) {
                            delete(pelotasEstaticas[cont]);
                            pelotasEstaticas.erase(pelotasEstaticas.begin() + cont);
                            break;
                        }
                    }
                    delete (pelotasEstaticas[i]);
                    pelotasEstaticas.erase(pelotasEstaticas.begin() + i);
                    actual->setPosX(0);
                    actual->setPosY(0);
                    actual->setPosZ(4);
                    glutPostRedisplay();
                    return;
                    break;
                default:
                    break;
            }
        }
        glutPostRedisplay();
        actual->setPosX(actual->getPosX() + velX);
        actual->setPosY(actual->getPosY() + velY);
        actual->setPosZ(actual->getPosZ() - 1);
    }
    
    glutTimerFunc(100, myTimer, 1);
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

    glTranslatef (0, 0.0, -.5);
    glBegin(GL_QUADS);

    //Arriba (amarillo)
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f( -medida, medida, -60 );
    glVertex3f(  medida, medida, -60 );
    glVertex3f(  medida, medida,  60 );
    glVertex3f( -medida, medida,  60 );

    glColor3f(1.0, 1.0, 1.0);
    //Atrás (blanco)
    glVertex3f( -medida, -medida, -60 );
    glVertex3f(  medida, -medida, -60 );
    glVertex3f(  medida,  medida, -60 );
    glVertex3f( -medida,  medida, -60 );

    //Derecha (verde)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f( medida, -medida, -60 );
    glVertex3f( medida,  medida, -60 );
    glVertex3f( medida,  medida,  60 );
    glVertex3f( medida, -medida,  60 );

    //Izquierda (azul)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f( -medida, -medida, -60 );
    glVertex3f( -medida, -medida,  60 );
    glVertex3f( -medida,  medida,  60 );
    glVertex3f( -medida,  medida, -60 );

    //Abajo (magenta)
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f( -medida, -medida, -60 );
    glVertex3f(  medida, -medida, -60 );
    glVertex3f(  medida, -medida,  60 );
    glVertex3f( -medida, -medida,  60 );

    glEnd();

    glPopMatrix();


    glColor3ub(0, 0, 0);
    glPushMatrix();
    glLineWidth(5);
    glTranslatef (actual->getPosX(), actual->getPosY(), actual->getPosZ() );
    glScalef (.5, .5, .2);
    glRotatef(actual->getPosZ(), 1.0, 1.0, 1.0);
    glutSolidSphere(1, 20, 20);
    glColor3ub(0, 0, 255);
    glutWireSphere(1, 20, 20);
    glPopMatrix();
    
    for (int i=0; i<pelotasEstaticas.size(); i++) {
        glPushMatrix();
        glLineWidth(5);
        glTranslatef (pelotasEstaticas[i]->getPosX(), pelotasEstaticas[i]->getPosY(), pelotasEstaticas[i]->getPosZ() );
        glScalef (.5, .5, .2);
        glutSolidSphere(1, 20, 20);
        glColor3ub(0, 0, 255);
        glutWireSphere(1, 20, 20);
        glPopMatrix();
    }

    glutSwapBuffers();
}


void keyboard(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
        case 27: exit(0); break;
        
            case 't':
            isMoving=true;
            velY=-1;
            velX= 2;
            glutTimerFunc(100, myTimer, 1);
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
