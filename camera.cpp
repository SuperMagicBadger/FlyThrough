#include "camera.h"

//camera-----------------------------------------
//constructors---------------
camera::camera(){
    followedC = NULL;
    followedE = NULL;
    watchedC = NULL;
    watchedE = NULL;    
}
camera::~camera(){    
}
//access---------------------
void camera::getPosition(float& x, float& y, float& z){
    
}
//manips---------------------
void camera::follow(entity* e){    
    followedE = e;
    followedC = NULL;
}
void camera::follow(curve* c){
    followedE = NULL;
    followedC = c;
    if(followedC == watchedC){
        followedItr = watchedItr;
        watchedItr++;
    } else {
        followedItr = c->CRbegin();\
    }
}
void camera::watch(entity* e){
    watchedE = e;
    watchedC =  NULL;
}
void camera::watch(curve* c){
    watchedE = NULL;
    watchedC = c;
    if(watchedC == followedC){
        watchedItr = followedItr;
        watchedItr++;
        watchedItr++;
        watchedItr++;
    } else {
        watchedItr = c->CRbegin();
    }
}
void camera::move(float x, float y, float z){
    followedE = NULL;
    followedC = NULL;
    posx = x;
    posy = y;
    posz = z;
}
void camera::face(float x, float y, float z){
    watchedE = NULL;
    watchedC = NULL;
    facx = x;
    facy = y;
    facz = z;
}
//update functions-----------
void camera::draw(){
    //set up viewing frustum
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    double aspect = double(w) / double(h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, aspect, 0.1/*znear*/, 50/*zfar*/);
    gluLookAt(posx, posy, posz, // eye
            facx, facy, facz, // center
            0.0, 1.0, 0.0); // up vector    
}
void camera::onUpdate(float timeElapsed){
    //update position
    if(followedE != NULL){
        followedE->getPosition(posx, posy, posz);
    }else if(followedC != NULL){
        posx = followedItr->x;
        posy = followedItr->y;
        posz = followedItr->z;
        followedItr++;
        if(followedItr == followedC->CRend()){
            cout << "end" << endl;
            followedItr = followedC->CRbegin();
        }
    }
    //update facing
    if(watchedE != NULL){
        watchedE->getPosition(facx, facy, facz);
    } else if(watchedC != NULL){
        facx = watchedItr->x;
        facy = watchedItr->y;
        facz = watchedItr->z;
        watchedItr++;
        if(watchedItr == watchedC->CRend()){
            cout << "end" << endl;
            watchedItr = watchedC->CRbegin();
        }
    }
    //check for doble reset
    if(watchedC != NULL && watchedC == followedC){
        if(watchedItr == watchedC->CRend()){
            cout << "end" << endl;
            watchedItr = watchedC->CRbegin();
            followedItr = watchedItr;
            watchedItr++;
        }        
    }
}
//camera=========================================
