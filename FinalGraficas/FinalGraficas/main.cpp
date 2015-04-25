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
#include "Sound.h"

using namespace std;

int windowWidth = 800, windowHeight = 800;

Sound sonido = Sound("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/music.wav");
bool isPlayingSound = true;
int tiempoSonido = 0;
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
bool gameOver = false, winGame = false, pausa = false, pausaInstrucciones = false;
std::ostringstream strStream;

bool menuInicial = false;
bool menuNivel = false;
bool instrucciones = false;
bool seleccion_1 = false, seleccion_2 = false, seleccion_3 = false, seleccion_v = false;
bool pantallaInicio = true;

static GLuint texName[40];
int texNumber = -1;

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

void loadImage(string nombreImagen, int numImagen)
{
    Image* image;
    //string ruta = "C:\\Users\\Marialicia\\Documents\\Tec\\8 Semestre\\Graficas\\Proyecto final\\smashJunkFood\\imagenes\\" + nombreImagen;
    string ruta = "/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/imagenes/" + nombreImagen;
    image = loadBMP(ruta.c_str());
    loadTexture(image,numImagen);
    delete image;
}

void initRendering()
{
    GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glGenTextures(39, texName); //Make room for our texture

	loadImage("volver2.bmp",++texNumber);
	loadImage("pared.bmp",++texNumber);
	loadImage("jugar1.bmp",++texNumber);
	loadImage("jugar2.bmp",++texNumber);
	loadImage("volver1.bmp",++texNumber);
	loadImage("i1-1.bmp",++texNumber);
	loadImage("i1-2.bmp",++texNumber);
	loadImage("i2-1.bmp",++texNumber);
	loadImage("i2-2.bmp",++texNumber);
	loadImage("i3-1.bmp",++texNumber);
	loadImage("i3-2.bmp",++texNumber);
	loadImage("i4-1.bmp",++texNumber);
	loadImage("i4-2.bmp",++texNumber);
	loadImage("i5-1.bmp",++texNumber);
	loadImage("i5-2.bmp",++texNumber);
	loadImage("smash.bmp",++texNumber);
	loadImage("junk.bmp",++texNumber);
	loadImage("food.bmp",++texNumber);
	loadImage("inicio1.bmp",++texNumber);
	loadImage("inicio2.bmp",++texNumber);
	loadImage("objetivo.bmp",++texNumber);
	loadImage("escuela.bmp",++texNumber);
	loadImage("materia.bmp",++texNumber);
	loadImage("autores.bmp",++texNumber);
	loadImage("instrucciones1.bmp",++texNumber);
	loadImage("instrucciones2.bmp",++texNumber);
	loadImage("salir1.bmp",++texNumber);
	loadImage("salir2.bmp",++texNumber);
	loadImage("facil1.bmp",++texNumber);
	loadImage("facil2.bmp",++texNumber);
	loadImage("intermedio1.bmp",++texNumber);
	loadImage("intermedio2.bmp",++texNumber);
	loadImage("dificil1.bmp",++texNumber);
	loadImage("dificil2.bmp",++texNumber);
	loadImage("metaJuego.bmp",++texNumber);
	loadImage("nuevoJuego1.bmp",++texNumber);
	loadImage("nuevoJuego2.bmp",++texNumber);
	loadImage("ganador.bmp",++texNumber);
	loadImage("perdedor.bmp",++texNumber);
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
        if (isMoving && !menuInicial && !menuNivel && !instrucciones && !pausa && !gameOver && !winGame && !pantallaInicio && !pausaInstrucciones) {

            if (actual->getPosX()>=9 || actual->getPosX()<=-9) {
                velX*=-1;
            }
            if (actual->getPosY()>=9 || actual->getPosY()<=-9) {
                velY*=-1;
            }
            if (actual->getPosZ()<=-60) {
                initValues();
                actual->setPosX(0);
                actual->setPosY(0);
                actual->setPosZ(-20);
                actual->setTipo(getRandomTipo());
                glutPostRedisplay();
                return;
            }
            for (int i = 0; i<pelotasEstaticas.size() && i >=0; i++) {
                switch (pelotasEstaticas[i]->checarColision(actual)) {
                    case 0:
                        break;
                    case 1:
                        initValues();
                        actual->setPosX(0);
                        actual->setPosY(0);
                        actual->setPosZ(-20);
                        actual->setTipo(getRandomTipo());
                        break;
                    case 2:
                        initValues();
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
                        if(pelotasEstaticas.empty()) {
                            winGame = true;
                            freeVector();
                        }
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

        if(!pausa && !menuInicial && !menuNivel && !instrucciones && !gameOver && !winGame && !pantallaInicio && !pausaInstrucciones) {
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

void sonidoF( int v){
    if (isPlayingSound) {
        tiempoSonido++;
        if (tiempoSonido >= 43) {
            tiempoSonido = 0;
            sonido.PlaySound();
        }
    }
    glutTimerFunc(1000,sonidoF,2);
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    sonido.PlaySound();
    glutTimerFunc(1000,sonidoF,2);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}

void initModels(){
    model[0] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/donut1.obj");

    glmUnitize(&model[0]);
    glmVertexNormals(&model[0], 90.0, GL_TRUE);

    model[1] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/cake.obj");
    glmUnitize(&model[1]);
    glmVertexNormals(&model[1], 90.0, GL_TRUE);
    model[2] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/donut4.obj");
    glmUnitize(&model[2]);
    glmVertexNormals(&model[2], 90.0, GL_TRUE);
    model[3] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/pie.obj");
    glmUnitize(&model[3]);
    glmVertexNormals(&model[3], 90.0, GL_TRUE);
    model[4] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/pizza1.obj");
    glmUnitize(&model[4]);
    glmVertexNormals(&model[4], 90.0, GL_TRUE);
    model[5] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/donut2.obj");
    glmUnitize(&model[5]);
    glmVertexNormals(&model[5], 90.0, GL_TRUE);
    model[6] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/pizza3.obj");
    glmUnitize(&model[6]);
    glmVertexNormals(&model[6], 90.0, GL_TRUE);
    model[7] = *glmReadOBJ("/Users/roberto/Documents/ITC/8vo/Graficas/finalGraficas/FinalGraficas/FinalGraficas/modelos3d/hamburger2.obj");

    glmUnitize(&model[7]);
    glmVertexNormals(&model[7], 90.0, GL_TRUE);

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

void resetJuego()
{
    actual = new  Pelota(0,0,-20,0);
    isMoving = false;
    time2 = "0:00";
    scoreS = "Score: ";
    pausa = false;
    pausaInstrucciones = false;
}

void opcionVolver()
{
    //Opcion: Volver a menu principal
    if(seleccion_v) glBindTexture(GL_TEXTURE_2D, texName[0]);
    else glBindTexture(GL_TEXTURE_2D, texName[4]);
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (-2.3, 1.7, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -0.7, -0.3, -2.0 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  0.7, -0.3, -2.0 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  0.7,  0.3, -2.0 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -0.7,  0.3, -2.0 );
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void ultimasDosOpciones(int textura11, int textura12, int textura21, int textura22)
{
    //Opcion 2: Instrucciones o Intermedio o Volver a jugar
    if(seleccion_2) glBindTexture(GL_TEXTURE_2D, texName[textura12]);
    else glBindTexture(GL_TEXTURE_2D, texName[textura11]);
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (0, -2.5, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -3.0, -0.3, -2.0 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  3.0, -0.3, -2.0 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  3.0,  0.3, -2.0 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -3.0,  0.3, -2.0 );
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //Opcion 3: Salir o Dificil
    if(seleccion_3) glBindTexture(GL_TEXTURE_2D, texName[textura22]);
    else glBindTexture(GL_TEXTURE_2D, texName[textura21]);
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (0, -3.5, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -3.0, -0.3, -2.0 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  3.0, -0.3, -2.0 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  3.0,  0.3, -2.0 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -3.0,  0.3, -2.0 );
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void tituloPantallaInicio(int textura, float x, float y)
{
    glBindTexture(GL_TEXTURE_2D, texName[textura]);
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (x, y, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -1.5, -0.5, -2.0 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  1.5, -0.5, -2.0 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  1.5,  0.5, -2.0 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -1.5,  0.5, -2.0 );
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void mostrarMenu()
{
    //Opcion 1: Jugar o Facil
    if(menuInicial) {
        if(seleccion_1) glBindTexture(GL_TEXTURE_2D, texName[3]);
        else glBindTexture(GL_TEXTURE_2D, texName[2]);
    } else if(menuNivel) {
        if(seleccion_1) glBindTexture(GL_TEXTURE_2D, texName[29]);
        else glBindTexture(GL_TEXTURE_2D, texName[28]);
    }
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (0, -1.5, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -3.0, -0.3, -2.0 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  3.0, -0.3, -2.0 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  3.0,  0.3, -2.0 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -3.0,  0.3, -2.0 );
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    if(menuInicial) {
        ultimasDosOpciones(24,25,26,27);
    } else if(menuNivel) {
        ultimasDosOpciones(30,31,32,33);
        opcionVolver();
    }

    //Smash
    tituloPantallaInicio(15,-0.1,1.7);
    //Junk
    tituloPantallaInicio(16,-1.5,0.7);
    //Food
    tituloPantallaInicio(17,1.5,0.7);
}

void mostrarInstrucciones(int tex, float posX, float posY, float sizeX, float sizeY)
{
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (posX, posY, 0);
    glBindTexture(GL_TEXTURE_2D, texName[tex]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -sizeX, -sizeY, 0 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  sizeX, -sizeY, 0 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  sizeX,  sizeY, 0 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -sizeX,  sizeY, 0 );
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void mostrarFinJuego()
{
    ultimasDosOpciones(35,36,26,27);

    if(winGame) glBindTexture(GL_TEXTURE_2D, texName[37]);
    else glBindTexture(GL_TEXTURE_2D, texName[38]);
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (-0.1, 0.7, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -2.5, -0.5, -2.0 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  2.5, -0.5, -2.0 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  2.5,  0.5, -2.0 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -2.5,  0.5, -2.0 );
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glLineWidth(5);
    glColor3ub(103, 152, 208);
    despliegaTexto("Score: " + getStringFromInt(score),-0.9,-0.5,0.003,0.003);
    glLineWidth(1);
}

void creditosPantallaInicio(int textura, float x, float y)
{
    glBindTexture(GL_TEXTURE_2D, texName[textura]);
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (x, y, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -2.4, -0.3, -2.0 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  2.4, -0.3, -2.0 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  2.4,  0.3, -2.0 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -2.4,  0.3, -2.0 );
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void mostrarPantallaInicio()
{
    //Boton inicio
    if(seleccion_3) glBindTexture(GL_TEXTURE_2D, texName[19]);
    else glBindTexture(GL_TEXTURE_2D, texName[18]);
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (0, -3.5, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -3.0, -0.3, -2.0 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  3.0, -0.3, -2.0 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  3.0,  0.3, -2.0 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -3.0,  0.3, -2.0 );
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //Smash
    tituloPantallaInicio(15,-0.1,1.7);
    //Junk
    tituloPantallaInicio(16,-1.5,0.7);
    //Food
    tituloPantallaInicio(17,1.5,0.7);
    //Objetivo
    creditosPantallaInicio(20,-0.1,-0.1);
    //Escuela
    creditosPantallaInicio(21,-0.1,-1.1);
    //Materia
    creditosPantallaInicio(22,-0.1,-1.8);
    //Autores
    creditosPantallaInicio(23,-0.1,-2.5);
}

void llamarMostrarInstrucciones()
{
    glBindTexture(GL_TEXTURE_2D, texName[34]);
    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (0, 0.8, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -2.0, -0.3, -2.0 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  2.0, -0.3, -2.0 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  2.0,  0.3, -2.0 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -2.0,  0.3, -2.0 );
    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    mostrarInstrucciones(5,-1.0,-0.3,0.3,0.3);
    mostrarInstrucciones(6,0.5,-0.3,0.8,0.3);
    mostrarInstrucciones(7,-1.0,-1.0,0.3,0.3);
    mostrarInstrucciones(8,0.5,-1.0,0.8,0.3);
    mostrarInstrucciones(9,-1.0,-1.7,0.3,0.3);
    mostrarInstrucciones(10,0.5,-1.7,0.8,0.3);
    mostrarInstrucciones(11,-1.0,-2.4,0.3,0.3);
    mostrarInstrucciones(12,0.5,-2.4,0.8,0.3);
    mostrarInstrucciones(13,-1.0,-3.1,0.3,0.3);
    mostrarInstrucciones(14,0.5,-3.1,0.6,0.3);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glTranslatef (0, 0.0, -.5);
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    glBegin(GL_QUADS);

    //Arriba
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -medida, medida, -60 );
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(  medida, medida, -60 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  medida, medida,  60 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( -medida, medida,  60 );

    //Atrás
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -medida, -medida, -60 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  medida, -medida, -60 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(  medida,  medida, -60 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -medida,  medida, -60 );

    //Derecha
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( medida, -medida, -60 );
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( medida,  medida, -60 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( medida,  medida,  60 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( medida, -medida,  60 );

    //Izquierda
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -medida, -medida, -60 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( -medida, -medida,  60 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( -medida,  medida,  60 );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -medida,  medida, -60 );

    //Abajo
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -medida, -medida, -60 );
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(  medida, -medida, -60 );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(  medida, -medida,  60 );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( -medida, -medida,  60 );

    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

	if(pantallaInicio) {
        mostrarPantallaInicio();
	}
	else if(menuInicial || menuNivel) {
        mostrarMenu();
        //Hamburguesa
        glPushMatrix();
		glLineWidth(5);
		glScalef(0.3,0.3,1.0);
		glTranslatef (0, -2.0, 0);
        glRotatef(90, 1, 1, 0);
		glmDraw(&model[7], GLM_SMOOTH | GLM_MATERIAL);
		glPopMatrix();
		//Dona
		glPushMatrix();
		glLineWidth(5);
		glScalef(0.3,0.3,1.0);
		glTranslatef (-2.7, -1.7, 0);
        glRotatef(90, 1, 1, 0);
		glmDraw(&model[0], GLM_SMOOTH | GLM_MATERIAL);
		glPopMatrix();
		//Pie
		glPushMatrix();
		glLineWidth(5);
		glScalef(0.3,0.3,1.0);
		glTranslatef (2.7, -1.7, 0);
        glRotatef(90, 1, 1, 0);
		glmDraw(&model[3], GLM_SMOOTH | GLM_MATERIAL);
		glPopMatrix();
    }
    else if(instrucciones) {
        llamarMostrarInstrucciones();
        opcionVolver();
    }
    else if(gameOver || winGame) {
        mostrarFinJuego();
        //Cake
        glPushMatrix();
		glLineWidth(5);
		glScalef(0.3,0.3,1.0);
		glTranslatef (0, -3.3, 0);
        glRotatef(90, 1, 1, 0);
		glmDraw(&model[1], GLM_SMOOTH | GLM_MATERIAL);
		glPopMatrix();
		//Dona
		glPushMatrix();
		glLineWidth(5);
		glScalef(0.3,0.3,1.0);
		glTranslatef (-2.7, -3.9, 0);
        glRotatef(90, 1, 1, 0);
		glmDraw(&model[2], GLM_SMOOTH | GLM_MATERIAL);
		glPopMatrix();
		//Pizza
		glPushMatrix();
		glLineWidth(5);
		glScalef(0.3,0.3,1.0);
		glTranslatef (2.7, -3.9, 0);
        glRotatef(90, 1, 1, 0);
		glmDraw(&model[4], GLM_SMOOTH | GLM_MATERIAL);
		glPopMatrix();
    }
    else {
        opcionVolver();
        if(pausa) {
            glColor3ub(91, 194, 167);
            glLineWidth(7);
            despliegaTexto("Pausa",-0.98,-1.05,0.0055,0.0055);
            glLineWidth(1);
        }
        if(pausaInstrucciones) {
            llamarMostrarInstrucciones();
        }
		//glColor3ub(0, 0, 0);

		glPushMatrix();
		//glLineWidth(5);
		glTranslatef (actual->getPosX(), actual->getPosY(), actual->getPosZ() );
		glScalef (1, 1, 1);
        glRotatef(90, 1, 1, 0);
		//glutSolidSphere(1, 20, 20);
		//glColor3ub(0, 0, 255);
		//glutWireSphere(1, 20, 20);
        glmDraw(&model[actual->getTipo()], GLM_SMOOTH | GLM_MATERIAL);
		glPopMatrix();

		for (int i=0; i<pelotasEstaticas.size(); i++) {
			glPushMatrix();
			//glLineWidth(5);
			glTranslatef (pelotasEstaticas[i]->getPosX(), pelotasEstaticas[i]->getPosY(), pelotasEstaticas[i]->getPosZ() );
			glScalef (1, 1, 1);
            //glutSolidSphere(1, 20, 20);
			//glColor3ub(0, 0, 255);
			//glutWireSphere(1, 20, 20);
            glRotatef(90, 1, 1, 0);
            glmDraw(&model[pelotasEstaticas[i]->getTipo()], GLM_SMOOTH | GLM_MATERIAL);
			glPopMatrix();
		}

		glColor3ub(0, 0, 0);
		glLineWidth(5);
		despliegaTexto(scoreS + getStringFromInt(score),1.0,1.2,0.002,0.002);
		despliegaTexto(time2,-.4,1.2,0.002,0.002);
		strStream << velX;
		despliegaTexto("Vel X: "+ strStream.str(),-2.3,-3,0.002,0.002);
		strStream.str("");
		strStream << velY;
		despliegaTexto("Vel Y: "+ strStream.str(),-2.3,-3.3,0.002,0.002);
		strStream.str("");
		glLineWidth(1);
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
            if (!isMoving && !menuInicial && !menuNivel && !instrucciones && !gameOver && !winGame && !pantallaInicio) {
                isMoving=true;
                glutTimerFunc(100, myTimer, 1);
            }
            break;
        case 'p':
        case 'P':
            if (!menuInicial && !menuNivel && !instrucciones && !gameOver && !winGame && !pantallaInicio) {
                if (pausa){
                    pausa = false;
                }
                else{
                    pausa = true;
                    glutPostRedisplay();
                }
            }
            break;
        case 'i':
        case 'I':
            if (!menuInicial && !menuNivel && !instrucciones && !gameOver && !winGame && !pantallaInicio) {
                if (pausaInstrucciones){
                    pausaInstrucciones = false;
                }
                else{
                    pausaInstrucciones = true;
                    glutPostRedisplay();
                }
            }
            break;
        case 'm':
        case 'M':
            if(isPlayingSound){
                sonido.StopSound();
                isPlayingSound = false;
            }
            else{
                sonido.PlaySound();
                isPlayingSound = true;
            }
            break;
        default:
            break;
    }
}

void specialKeys (int key, int x, int y){
    if(!menuInicial && !menuNivel && !instrucciones && !gameOver && !winGame && !pantallaInicio && !pausa && !pausaInstrucciones) {
		switch (key) {
			case GLUT_KEY_UP:
				if (!isMoving && actual->getPosY()+1 <9) {
					actual->setPosY(actual->getPosY()+1);
					glutPostRedisplay();
				}
				break;
			case GLUT_KEY_DOWN:
				if (!isMoving && actual->getPosY()-1 >-9) {
					actual->setPosY(actual->getPosY()-1);
					glutPostRedisplay();
				}
				break;
			case GLUT_KEY_RIGHT:
				if (!isMoving && actual->getPosX()+1 < 9) {
					actual->setPosX(actual->getPosX()+1);
					glutPostRedisplay();
				}
				break;
			case GLUT_KEY_LEFT:
				if (!isMoving && actual->getPosX()-1 >-9) {
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
        if(menuInicial || menuNivel || gameOver || winGame || pantallaInicio) {
            xIzq = windowWidth*39/800; xDer = windowWidth*760/800;
            yUp_1 = windowHeight*429/800; yDown_1 = windowHeight*495/800;
            yUp_2 = windowHeight*547/800; yDown_2 = windowHeight*615/800;
            yUp_3 = windowHeight*667/800; yDown_3 = windowHeight*736/800;
            if(x >= xIzq && x <= xDer && (y >= yUp_1 && y <= yDown_1 || y >= yUp_2 && y <= yDown_2 || y >= yUp_3 && y <= yDown_3)) {
                if(y >= yUp_1 && y <= yDown_1) {
                    if(menuInicial) {
                        menuInicial = false;
                        menuNivel = true;
                    }
                    else if(menuNivel) {
                        dificultad = 0;
                        t = 3;
                        menuNivel = false;
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
                    else if(gameOver || winGame) {
                        resetJuego();
                        gameOver = false;
                        winGame = false;
                        menuNivel = true;
                    }
                }
                else if(y >= yUp_3 && y <= yDown_3) {
                    if(menuInicial || gameOver || winGame) {
                        exit(0);
                    }
                    else if(menuNivel) {
                        dificultad = 2;
                        t = 450;
                        menuNivel = false;
                        initGame();
                    }
                    else if(pantallaInicio) {
                        pantallaInicio = false;
                        menuInicial = true;
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
        else {
            if(x >= xIzq_volver && x <= xDer_volver && y >= yUp_volver && y <= yDown_volver) {
                resetJuego();
                menuNivel = true;
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
    if(menuInicial || menuNivel || gameOver || winGame || pantallaInicio) {
        xIzq = windowWidth*39/800; xDer = windowWidth*760/800;
        yUp_1 = windowHeight*429/800; yDown_1 = windowHeight*495/800;
        yUp_2 = windowHeight*547/800; yDown_2 = windowHeight*615/800;
        yUp_3 = windowHeight*667/800; yDown_3 = windowHeight*736/800;
        if(x >= xIzq && x <= xDer && (y >= yUp_1 && y <= yDown_1 || y >= yUp_2 && y <= yDown_2 || y >= yUp_3 && y <= yDown_3)) {
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
    else if(x >= xIzq_volver && x <= xDer_volver && y >= yUp_volver && y <= yDown_volver) {
        seleccion_v = true;
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
