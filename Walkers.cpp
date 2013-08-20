#include "Walkers.h"

//walkers--------------------------------------------------
Model_PLY walker::Head;
Model_PLY walker::Torso;
Model_PLY walker::RArm;
Model_PLY walker::LArm;
Model_PLY walker::RLeg;
Model_PLY walker::LLeg;
void walker::init(){
    Head.LoadModel("mmodels/head.ply");
    Torso.LoadModel("mmodels/body.ply");
}

//constructors---------------
walker::walker(){
}
walker::~walker(){
}
//access---------------------
bool walker::walking(){
    return isWalking && !toNeutral;
}
bool walker::idleing(){
    return !isWalking && !toNeutral;
}
void walker::getPosition(float& x, float& y, float& z){
    
}
//manips---------------------
void walker::walking(bool walk){
    toNeutral = true;
    isWalking = walk;
}
//update functions-----------
void walker::onUpdate(float timeElapsed){
    if(toNeutral) returnToNeutral(timeElapsed);
    else if(isWalking) walk(timeElapsed);
    else idle(timeElapsed);
}
void walker::draw(){
    glPushMatrix();
    glTranslatef(0, 2.5, 0);
    Head.Draw();
    glPopMatrix();
    Torso.Draw();
    LArm.Draw();
    RArm.Draw();
    LLeg.Draw();
    RLeg.Draw();
}
//private animations---------
void walker::returnToNeutral(float time){
    
}
void walker::idle(float time){
    
}
void walker::walk(float time){
    
}
//walkers==================================================
