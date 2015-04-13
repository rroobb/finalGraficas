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
#include "glm.h"
#include <stdlib.h>
#include <stdio.h>
#include "Pelota.h"
#include <vector>
#include <string>
#include <sstream>
#include "imageloader.h"
#include <fstream>

using namespace std;

int windowWidth = 800, windowHeight = 800;

Pelota *actual = new  Pelota(0,0,-20,0);
int listaPelota, listaFondo;
float velX,velY;
bool isMoving = false;
int dificultad;
vector<Pelota*> pelotasEstaticas;
GLMmodel model[8] ;
const float medida = 10.0;
int score, t;
string time2 = "0:00";
string scoreS = "Score: ";
bool gameOver = false, pausa = false;
std::ostringstream strStream;

bool menuInicial = true;
bool menuNivel = false;
bool instrucciones = false;
bool seleccion_1 = false, seleccion_2 = false, seleccion_3 = false, seleccion_v = false;

string instruccionesTxt = "Instrucciones",
jugarTxt = "Jugar",
salirTxt = "Salir",
facilTxt = "Facil",
medioTxt = "Intermedio",
dificilTxt = "Dificil",
volverTxt = "Volver";

static GLuint texName[1];

void formato (int i){
    time2[0]= '0' + t/60;
    time2[2]= '0' + (t/10) % 6;
    time2[3]= '0' + t % 10;
}

float getRandomVel(){
    float aux = rand() % 11;
    aux/= 10;
    float num = rand() % 11;
    if (num > 5) {
        aux*= -1;
    }
    return aux;
}

void initValues(){
    velX = getRandomVel();
    velY = getRandomVel();
    isMoving = false;
}

void despliegaTexto(string texto, float x, float y, float sizeX, float sizeY) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x,y,0);
    glScalef(sizeX, sizeY, 1.0);

    for (int k=0;k<texto.length(); k++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN,texto[k]);

    glPopMatrix();
}

void reshape (int w, int h)
{
    windowWidth = w;
    windowHeight = h;
	glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 1.0f, -6.0f);
}

//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{

    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data

}

void initRendering()
{
    GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glGenTextures(1, texName); //Make room for our texture
    Image* image;

    image = loadBMP("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/imagenes/instrucciones.bmp");
    loadTexture(image,0);

    delete image;
}

int getRandomTipo(){

    int tipo = 0;
    switch (dificultad) {
        case 0: //facil
            tipo = rand() % 5;
            break;
        case 1: //medio
            tipo = rand() % 6;
            break;
        case 2: //dificil
            tipo = rand() % 8;
            break;
        default:
            break;
    }
    return tipo;
}

void initLevel1(){
    pelotasEstaticas.push_back(new Pelota(-9, 9, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(0, 0, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(9, 9, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(-9, -9, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(9, -9, -60, getRandomTipo()));
}

void initLevel2(){
    initLevel1();
    pelotasEstaticas.push_back(new Pelota(-4, -4, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(-4, 4, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(4, 4, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(4, -4, -60, getRandomTipo()));
}

void initLevel3(){
    initLevel2();
    pelotasEstaticas.push_back(new Pelota(0, -9, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(0, 9, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(-9, 0, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(9, 0, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(0, -4, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(0, 4, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(-4, 0, -60, getRandomTipo()));
    pelotasEstaticas.push_back(new Pelota(4, 0, -60, getRandomTipo()));
}

void freeVector(){
    for (int i=0; i<pelotasEstaticas.size(); i++) {
        delete(pelotasEstaticas[i]);
    }
    pelotasEstaticas.clear();
}

void myTimer(int v)
{
    if (v == 1) {
        if (isMoving && !menuInicial && !menuNivel && !instrucciones && !pausa) {

            if (actual->getPosX()>=9 || actual->getPosX()<=-9) {
                velX*=-1;
            }
            if (actual->getPosY()>=9 || actual->getPosY()<=-9) {
                velY*=-1;
            }
            if (actual->getPosZ()<=-60) {
                initValues();
                pelotasEstaticas.push_back(actual);
                actual = new Pelota(0,0,-20,getRandomTipo());
                glutPostRedisplay();
                return;
            }
            for (int i = 0; i<pelotasEstaticas.size() && i >=0; i++) {
                switch (pelotasEstaticas[i]->checarColision(actual)) {
                    case 0:
                        break;
                    case 1:
                        initValues();
                        if (actual->getPosZ()+1 >= -20) {
                            gameOver = true;
                            freeVector();
                            glutPostRedisplay();
                            return;
                        }
                        pelotasEstaticas.push_back(actual);
                        actual = new Pelota(0,0,-20,getRandomTipo());
                        glutPostRedisplay();
                        return;
                    case 3:
                        initValues();
                /*        actual->destruir();
                        pelotasEstaticas[i]->destruir();
                        pelotasEstaticas[i]->getColision()->destruir();*/
                        for (int cont=0; cont<pelotasEstaticas.size(); cont++) {
                            if (pelotasEstaticas[cont] == pelotasEstaticas[i]->getColision()) {
                                delete(pelotasEstaticas[cont]);
                                pelotasEstaticas.erase(pelotasEstaticas.begin() + cont);
                                if (cont < i ){
                                    i--;
                                }
                                break;
                            }
                        }
                        delete (pelotasEstaticas[i]);
                        pelotasEstaticas.erase(pelotasEstaticas.begin() + i);
                        actual->setPosX(0);
                        actual->setPosY(0);
                        actual->setPosZ(-20);
                        actual->setTipo(getRandomTipo());
                        score += 30;
                        glutPostRedisplay();
                        return;
                        break;
                    default:
                        break;
                }
            }
            actual->setPosX(actual->getPosX() + velX);
            actual->setPosY(actual->getPosY() + velY);
            actual->setPosZ(actual->getPosZ() - 1);
            glutPostRedisplay();

        }

        glutTimerFunc(100, myTimer, 1);
    }
    else if (v==2){

        if(!pausa && !menuInicial && !menuNivel && !instrucciones) {
            t--;
            if (t == 0) {
                gameOver = true;
                freeVector();
                glutPostRedisplay();
                return;
            }
            formato(t);
            glutPostRedisplay();
        }
            glutTimerFunc(1000,myTimer,2);

    }
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}

void initModels(){
    model[0] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/donut1.obj");
    glmUnitize(model);
    glmFacetNormals(model);
    glmVertexNormals(model, 90.0, GL_TRUE);
    model[1] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/cake.obj");
    glmUnitize(model+1);
    glmFacetNormals(model+1);
    glmVertexNormals(model+1, 90.0, GL_TRUE);
    model[2] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/donut4.obj");
    glmUnitize(model+2);
    glmFacetNormals(model+2);
    glmVertexNormals(model+2, 90.0, GL_TRUE);
    model[3] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/pie.obj");
    glmUnitize(model+3);
    glmFacetNormals(model+3);
    glmVertexNormals(model+3, 90.0, GL_TRUE);
    model[4] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/pizza1.obj");
    glmUnitize(model+4);
    glmFacetNormals(model+4);
    glmVertexNormals(model+4, 90.0, GL_TRUE);
    model[5] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/donut2.obj");
    glmUnitize(model+5);
    glmFacetNormals(model+5);
    glmVertexNormals(model+5, 90.0, GL_TRUE);
    model[6] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/pizza3.obj");
    glmUnitize(model+6);
    glmFacetNormals(model+6);
    glmVertexNormals(model+6, 90.0, GL_TRUE);
    model[7] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/hamburger2.obj");
    glmUnitize(model+7);
    glmFacetNormals(model+7);
    glmVertexNormals(model+7, 90.0, GL_TRUE);
}

void initGame(){
    score = 0;
    glutTimerFunc(1000, myTimer, 2);
    switch (dificultad) {
        case 0:
            initLevel1();
            break;
        case 1:
            initLevel2();
            break;
        case 2:
            initLevel3();
            break;
        default:
            break;
    }
    initValues();
    initModels();
    menuNivel = false;
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

void reverseString(char *ptr){
    char*aux=ptr;
    char*ptr2=ptr;
    char letra;
    if (ptr==NULL or  *ptr=='\0' or *(ptr+1)=='\0') {
        return;
    }
    while (*aux!='\0') {
        aux++;
    }
    aux--;
    while (aux>ptr) {
        letra=*ptr;
        *ptr=*aux;
        *aux=letra;
        ptr++;
        aux--;
    }
}

string getStringFromInt(int numero){
    if (numero == 0) {
        return "0";
    }
    int auxiliar;
    string numero2="";
    while(numero>0){
        auxiliar = numero % 10;
        numero2+= ('0'+auxiliar);
        numero/= 10;
    }
    char *ptr=&numero2[0];
    reverseString(ptr);
    return numero2;

}

void opcionVolver()
{
    //Opcion: Volver a menu principal
    if(seleccion_v) glColor3ub(139, 0, 139);
    else glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef (-2.3, 1.7, 0);
    glRotatef(1, 1.0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3f( -0.7, -0.3, -2.0 );
    glVertex3f(  0.7, -0.3, -2.0 );
    glVertex3f(  0.7,  0.3, -2.0 );
    glVertex3f( -0.7,  0.3, -2.0 );
    glEnd();
    glPopMatrix();
    glColor3ub(255, 255, 255);
    despliegaTexto(volverTxt,-2.15,0.95,0.0025,0.0025);
}

void mostrarMenu()
{
    glPushMatrix();

    //Opcion 1: Jugar o Facil
    if(seleccion_1) glColor3ub(139, 0, 139);
    else glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef (0, 1.0, 0);
    glRotatef(2, 1.0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3f( -1.5, -0.5, -2.0 );
    glVertex3f(  1.5, -0.5, -2.0 );
    glVertex3f(  1.5,  0.5, -2.0 );
    glVertex3f( -1.5,  0.5, -2.0 );
    glEnd();
    glPopMatrix();
    glColor3ub(255, 255, 255);
    if(menuInicial)
        despliegaTexto(jugarTxt,-0.8,0.4,0.005,0.005);
    else if(menuNivel)
        despliegaTexto(facilTxt,-0.7,0.3,0.005,0.005);

    //Opcion 2: Instrucciones o Intermedio
    if(seleccion_2) glColor3ub(139, 0, 139);
    else glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef (0, -1.0, 0);
    glRotatef(2, 1.0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3f( -1.4, -0.5, -2.0 );
    glVertex3f(  1.4, -0.5, -2.0 );
    glVertex3f(  1.4,  0.5, -2.0 );
    glVertex3f( -1.4,  0.5, -2.0 );
    glEnd();
    glPopMatrix();
    glColor3ub(255, 255, 255);
    if(menuInicial)
        despliegaTexto(instruccionesTxt,-0.95,-1.05,0.0025,0.0025);
    else if(menuNivel)
        despliegaTexto(medioTxt,-0.93,-1.07,0.003,0.003);

    //Opcion 3: Salir o Dificil
    if(seleccion_3) glColor3ub(139, 0, 139);
    else glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef (0, -3.0, 0);
    glRotatef(2, 1.0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3f( -1.5, -0.5, -2.0 );
    glVertex3f(  1.5, -0.5, -2.0 );
    glVertex3f(  1.5,  0.5, -2.0 );
    glVertex3f( -1.5,  0.5, -2.0 );
    glEnd();
    glPopMatrix();
    glColor3ub(255, 255, 255);
    if(menuInicial)
        despliegaTexto(salirTxt,-0.65,-2.7,0.005,0.005);
    else if(menuNivel)
        despliegaTexto(dificilTxt,-0.75,-2.7,0.005,0.005);

    if(menuNivel)
        opcionVolver();

    glPopMatrix();
}

void mostrarInstrucciones()
{
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (0, -1.3, 0);
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -2.3, -2.0, 0 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  2.3, -2.0, 0 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  2.3,  2.0, 0 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -2.3,  2.0, 0 );
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    opcionVolver();
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

	if(menuInicial || menuNivel) {
        mostrarMenu();
    }
    else if(instrucciones) {
        mostrarInstrucciones();
    }
    else {
		glColor3ub(0, 0, 0);
		glPushMatrix();
		glLineWidth(5);
		glTranslatef (actual->getPosX(), actual->getPosY(), actual->getPosZ() );

		glRotatef(actual->getPosZ(), 1.0, 1.0, 1.0);

		glColor3ub(0, 0, 255);
        
        glmDraw(model + actual->getTipo(),  GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);

        
		glPopMatrix();

		for (int i=0; i<pelotasEstaticas.size(); i++) {
			glPushMatrix();
			glLineWidth(5);
			glTranslatef (pelotasEstaticas[i]->getPosX(), pelotasEstaticas[i]->getPosY(), pelotasEstaticas[i]->getPosZ() );
			glScalef (1, 1, 1);
			glutSolidSphere(1, 20, 20);
			glColor3ub(0, 0, 255);
			glutWireSphere(1, 20, 20);
			glPopMatrix();
		}

		glColor3ub(0, 0, 0);

		despliegaTexto(scoreS + getStringFromInt(score),-2.5,1.2,0.002,0.002);

		despliegaTexto(time2,-.4,1.2,0.002,0.002);

		strStream << velX;

		despliegaTexto("Vel X: "+ strStream.str(),-2.5,-3,0.002,0.002);
		strStream.str("");
		strStream << velY;
		despliegaTexto("Vel Y: "+ strStream.str(),-2.5,-3.3,0.002,0.002);
		strStream.str("");
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;

        case 't':
        case 'T':
            if (!isMoving && !menuInicial && !menuNivel && !instrucciones) {
                isMoving=true;
                glutTimerFunc(100, myTimer, 1);
            }
            break;
        case 'p':
        case 'P':
            if (!menuInicial && !menuNivel && !instrucciones) {
                if (pausa){
                    pausa = false;
                }
                else{
                    pausa = true;
                }
            }
        default:
            break;
    }
}

void specialKeys (int key, int x, int y){
    if(!menuInicial && !menuNivel && !instrucciones) {
		switch (key) {
			case GLUT_KEY_UP:
				if (!isMoving && actual->getPosY()+1 <10) {
					actual->setPosY(actual->getPosY()+1);
					glutPostRedisplay();
				}
				break;
			case GLUT_KEY_DOWN:
				if (!isMoving && actual->getPosY()-1 >-10) {
					actual->setPosY(actual->getPosY()-1);
					glutPostRedisplay();
				}
				break;
			case GLUT_KEY_RIGHT:
				if (!isMoving && actual->getPosX()+1 < 10) {
					actual->setPosX(actual->getPosX()+1);
					glutPostRedisplay();
				}
				break;
			case GLUT_KEY_LEFT:
				if (!isMoving && actual->getPosX()-1 >-10) {
					actual->setPosX(actual->getPosX()-1);
					glutPostRedisplay();
				}
				break;
			default:
				break;
		}
	}
}

void myMouse(int button, int state, int x, int y)
{
    int xIzq, xDer, yUp_1, yDown_1, yUp_2, yDown_2, yUp_3, yDown_3;
    int yUp_volver = windowHeight*33/800, yDown_volver = windowHeight*103/800;
    int xIzq_volver = windowWidth*39/800, xDer_volver = windowWidth*205/800;
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        seleccion_1 = false; seleccion_2 = false; seleccion_2 = false; seleccion_v = false;
        if(menuInicial || menuNivel) {
            xIzq = windowWidth*222/800; xDer = windowWidth*578/800;
            yUp_1 = windowHeight*90/800; yDown_1 = windowHeight*207/800;
            yUp_2 = windowHeight*332/800; yDown_2 = windowHeight*448/800;
            yUp_3 = windowHeight*574/800; yDown_3 = windowHeight*689/800;
            if(x >= xIzq && x <= xDer) {
                if(y >= yUp_1 && y <= yDown_1) {
                    if(menuInicial) {
                        menuInicial = false;
                        menuNivel = true;
                    }
                    else if(menuNivel) {
                        dificultad = 0;
                        t = 600;
                        initGame();
                    }
                }
                else if(y >= yUp_2 && y <= yDown_2) {
                    if(menuInicial) {
                        menuInicial = false;
                        instrucciones = true;
                    }
                    else if(menuNivel) {
                        dificultad = 1;
                        t = 450;
                        menuNivel = false;
                        initGame();
                    }
                }
                else if(y >= yUp_3 && y <= yDown_3) {
                    if(menuInicial) {
                        exit(0);
                    }
                    else if(menuNivel) {
                        dificultad = 2;
                        t = 450;
                        menuNivel = false;
                        initGame();
                    }
                }
            }
            else if(x >= xIzq_volver && x <= xDer_volver && menuNivel) {
                if(y >= yUp_volver && y <= yDown_volver) {
                    menuNivel = false;
                    menuInicial = true;
                }
            }
        }
        else if(instrucciones) {
            if(x >= xIzq_volver && x <= xDer_volver && y >= yUp_volver && y <= yDown_volver) {
                instrucciones = false;
                menuInicial = true;
            }
        }
        glutPostRedisplay();
    }
}

void passive(int x, int y)
{
    int xIzq, xDer, yUp_1, yDown_1, yUp_2, yDown_2, yUp_3, yDown_3;
    int yUp_volver = windowHeight*33/800, yDown_volver = windowHeight*103/800;
    int xIzq_volver = windowWidth*39/800, xDer_volver = windowWidth*205/800;
    if(menuInicial || menuNivel) {
        xIzq = windowWidth*222/800; xDer = windowWidth*578/800;
        yUp_1 = windowHeight*90/800; yDown_1 = windowHeight*207/800;
        yUp_2 = windowHeight*332/800; yDown_2 = windowHeight*448/800;
        yUp_3 = windowHeight*574/800; yDown_3 = windowHeight*689/800;
        if(x >= xIzq && x <= xDer) {
            if(y >= yUp_1 && y <= yDown_1) {
                seleccion_1 = true;
            }
            else if(y >= yUp_2 && y <= yDown_2) {
                seleccion_2 = true;
            }
            else if(y >= yUp_3 && y <= yDown_3) {
                seleccion_3 = true;
            }
            else {
                seleccion_1 = false;
                seleccion_2 = false;
                seleccion_3 = false;
            }
        }
        else if(x >= xIzq_volver && x <= xDer_volver && menuNivel) {
            if(y >= yUp_volver && y <= yDown_volver) {
                seleccion_v = true;
            }
            else {
                seleccion_v = false;
            }
        }
        else {
            seleccion_v = false;
            seleccion_1 = false;
            seleccion_2 = false;
            seleccion_3 = false;
        }
    }
    else if(instrucciones) {
        if(x >= xIzq_volver && x <= xDer_volver && y >= yUp_volver && y <= yDown_volver) {
            seleccion_v = true;
        }
        else {
            seleccion_v = false;
        }
    }
    else {
        seleccion_v = false;
        seleccion_1 = false;
        seleccion_2 = false;
        seleccion_3 = false;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize (windowWidth,windowHeight);
    glutInitWindowPosition (0,0);
    glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB| GLUT_DEPTH);
    glutCreateWindow("Smash Junk Food");
    init();
	initRendering();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(500, myTimer, 1);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
	glutMouseFunc(myMouse);
    glutPassiveMotionFunc(passive);
    glutMainLoop();
    return 0;
}
