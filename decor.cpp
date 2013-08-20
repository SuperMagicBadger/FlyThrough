#include "decor.h"

//decoration-----------------------------------------------
//constructors-------------------------
decoration::decoration(){
    tX = tY = tZ = 0;
    sX = sY = sZ = 1;
    rD = rX = rY = rZ = 0; 
    
    r = g = 1;
    b = 0;
    
    matColor[0] = 1;
    matColor[1] = 0;
    matColor[2] = 0;
    matColor[3] = 1;
}
decoration::~decoration(){
    
}
//loadInformation----------------------
void decoration::LoadOBJ(char* file){
    decor.LoadModel(file);
}
void decoration::LoadTex(char* file){
    decor.LoadTexture(file);
}
//entity-------------------------------
void decoration::draw(){
    glMatrixMode(GL_MODELVIEW);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(tX, tY, tZ);
    glRotatef(rD, rX, rY, rZ);
    glScalef(sX, sY, sZ);
    decor.Draw();
    glPopMatrix();
}
void decoration::onUpdate(float timeElapsed){
    
}
void decoration::getPosition(float& x, float& y, float& z){
    x = tX;
    y = tY;
    z = tZ;
}
//position anipulation-----------------
void decoration::translate(float x, float y, float z){
    tX = x;
    tY = y;
    tZ = z;
}
void decoration::scale(float x, float y, float z){
    sX = x;
    sY = y;
    sZ = z;
}
void decoration::rotate(float deg, float x, float y, float z){
    rD = deg;
    rX = x;
    rY = y;
    rZ = z;
}
//decoration===============================================
