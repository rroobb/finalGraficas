//
//  Pelota.h
//  FinalGraficas
//
//  Created by Rob on 01/04/15.
//  Copyright (c) 2015 ITESM. All rights reserved.
//

class Pelota{
    private:
        float posX, posY, posZ, velX, velY, velZ, tipo;
        Pelota *colision;
    public:
    Pelota(int posX, int posY, int posZ, int velX, int velY, int velZ, int tipo);
    void setPosX(int x);
    void setTipo(int t);
    void setPosY(int y);
    void setPosZ(int z);
    void setVelX(int vx);
    void setVelY(int vy);
    void setVelZ(int vz);
    void setColision(Pelota *pelota);
    int getPosX();
    int getTipo();
    int getPosY();
    int getPosZ();
    int getVelZ();
    int getVelX();
    int getVelY();
    Pelota* getColision();
    int checarColision(Pelota pelota);
    
};

Pelota::Pelota(int posX, int posY, int posZ, int velX, int velY, int velZ, int tipo){
    this->colision = NULL;
   this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;
    this->velX = velX;
    this->velY = velY;
    this->tipo = tipo;
    this->velZ = velZ;
}

void Pelota::setPosX(int x){
    this->posX = x;
}
void Pelota::setTipo(int tipo){
    this->tipo = tipo;
}
void Pelota::setPosY(int y){
    this->posY = y;
}
void Pelota::setPosZ(int z){
    this->posZ = z;
}
void Pelota::setVelX(int vx){
    this->velX = vx;
}
void Pelota::setVelZ(int vz){
    this->velZ = vz;
}
void Pelota::setVelY(int vy){
    this->velY = vy;
}
void Pelota::setColision(Pelota *pelota){
    this->colision = pelota;
}
int Pelota::getPosX(){
    return this->posX;
}
int Pelota::getPosY(){
    return this->posY;
}


int Pelota::getPosZ(){
    return this->posZ;
}
int Pelota::getVelX(){
    return this->velX;
}
int Pelota::getVelZ(){
    return this->velZ;
}
int Pelota::getVelY(){
    return this->velY;
}
int Pelota::getTipo(){
    return this->tipo;
}
Pelota* Pelota::getColision(){
    return this->colision;
}

int Pelota::checarColision(Pelota pelota){
    //0: nada, 1: colision, 3 destruir bolas
    float radio = 5;
    int respuesta = 0;
    if (((this->posX-radio <= pelota.getPosX()-radio && this->posX+radio >= pelota.getPosX()-radio) ||
        (this->posX-radio <= pelota.getPosX()+radio && this->posX+radio >= pelota.getPosX()+radio)) &&
        ((this->posY-radio <= pelota.getPosY()-radio && this->posY+radio >= pelota.getPosY()-radio) ||
        (this->posY-radio <= pelota.getPosY()+radio && this->posY+radio >= pelota.getPosY()+radio)) &&
        ((this->posZ-radio <= pelota.getPosZ()-radio && this->posZ+radio >= pelota.getPosZ()-radio) ||
        (this->posZ-radio <= pelota.getPosZ()+radio && this->posZ+radio >= pelota.getPosZ()+radio))) {
            respuesta = 1;
    }
    
    if (respuesta == 1 && this->tipo == pelota.tipo)  {
        if(this->colision != NULL || pelota.colision != NULL)
           return 3;
        else{
            this->colision = &pelota;
            pelota.colision = this;
        }
    }
    return respuesta;
}
