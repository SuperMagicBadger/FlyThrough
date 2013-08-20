#include "actor.h"


//actor----------------------------------------------------
void actor::follow(curve* c){
    followed = c;
    itr = followed->CRbegin();
}
void actor::onUpdate(float timeE){
    //conditions--------
    if(followed == NULL) return;
    //------------------
    
    //varblok-----------
    float x, y, z;
    float x2, y2, z2;
    float degree;
    //------------------
    
    //nab points from itrs
    x = itr->x;
    y = itr->y;
    z = itr->z;
    itr++;
    if(itr == followed->CRend()) {
        itr = followed->CRbegin();
    }
    x2 = itr->x;
    y2 = itr->y;
    z2 = itr->z;
    //------------------
    
    //move--------------
    translate(x, y, z);
    //------------------
    
    //rotate------------
    degree = atan((x2 - x) / (z2 - z)) * 180 / 3.14159;
    rotate(degree, 0, 1, 0);
    //------------------
    
    
}
//actor====================================================