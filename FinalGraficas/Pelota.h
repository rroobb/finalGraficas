//
//  Pelota.h
//  FinalGraficas
//
//  Created by Rob on 01/04/15.
//  Copyright (c) 2015 ITESM. All rights reserved.
//

class Pelota{
    private:
        float posX, posY, posZ, tipo;
        Pelota *colision;
    public:
    Pelota(int posX, int posY, int posZ, int tipo);
    void setPosX(float x);
    void setTipo(int t);
    void setPosY(float y);
    void setPosZ(float z);
    void setColision(Pelota *pelota);
    float getPosX();
    int getTipo();
    float getPosY();
    float getPosZ();
    int getVelZ();
    int getVelX();
    int getVelY();
    Pelota* getColision();
    int checarColision(Pelota* pelota);
    void destruir();
    
};

Pelota::Pelota(int posX, int posY, int posZ, int tipo){
    this->colision = NULL;
   this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;
    this->tipo = tipo;

}

void Pelota::setPosX(float x){
    this->posX = x;
}
void Pelota::setTipo(int tipo){
    this->tipo = tipo;
}
void Pelota::setPosY(float y){
    this->posY = y;
}
void Pelota::setPosZ(float z){
    this->posZ = z;
}
void Pelota::setColision(Pelota *pelota){
    this->colision = pelota;
}
float Pelota::getPosX(){
    return this->posX;
}
float Pelota::getPosY(){
    return this->posY;
}

float Pelota::getPosZ(){
    return this->posZ;
}

int Pelota::getTipo(){
    return this->tipo;
}
Pelota* Pelota::getColision(){
    return this->colision;
}

int Pelota::checarColision(Pelota* pelota){
    //0: nada, 1: colision, 3 destruir bolas
    float radio = 1;
    int respuesta = 0;
    if (((this->posX-radio <= pelota->getPosX()-radio && this->posX+radio >= pelota->getPosX()-radio) ||
        (this->posX-radio <= pelota->getPosX()+radio && this->posX+radio >= pelota->getPosX()+radio)) &&
        ((this->posY-radio <= pelota->getPosY()-radio && this->posY+radio >= pelota->getPosY()-radio) ||
        (this->posY-radio <= pelota->getPosY()+radio && this->posY+radio >= pelota->getPosY()+radio)) &&
        ((this->posZ-radio <= pelota->getPosZ()-radio && this->posZ+radio >= pelota->getPosZ()-radio) ||
        (this->posZ-radio <= pelota->getPosZ()+radio && this->posZ+radio >= pelota->getPosZ()+radio))) {
            respuesta = 1;
    }
    
    if (respuesta == 1 && this->tipo == pelota->tipo)  {
        if(this->colision != NULL || pelota->colision != NULL)
           return 3;
        else{
            this->colision = pelota;
            pelota->colision = this;
        }
    }
    return respuesta;
}

void Pelota:: destruir(){
    
}
