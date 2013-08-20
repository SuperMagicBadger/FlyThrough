#include "car.h"

//car--------------------------------------------
//car constructors---------------------
car::car() {
    carLength = 1;
    carHeight = 1;
    axelWidthFront = .5;
    axelWidthBack = .5;

    carmodel = Model_OBJ();
    carmodel.Load("car.obj");

    wheel = Model_OBJ();
    wheel.Load("tire.obj");

    steering = Model_OBJ();
    steering.Load("steering.obj");

    chair = Model_OBJ();
    chair.Load("chair.obj");
    
    hubcap = Model_OBJ();
    hubcap.Load("hubcap.obj");
    
    suspTop = Model_OBJ();
    suspTop.Load("suspTop.obj");
    
    centerX = 0;
    centerY = 0;
    facingRot = 0;

    speed = 0;
    acceleration = 0;
    turnRate = 0;
    wheelRot = 0;

    suspensionHeight = 0;
}
car::~car() {
    carmodel.Release();
    wheel.Release();
    steering.Release();
    chair.Release();
    hubcap.Release();
}
//car update handlers------------------
void car::onUpdate(float timeElapsed) {
    if (speed != 0) {
        if (speed > 0) {
            facingRot -= turnRate * timeElapsed;
            wheelRot--;
        } else {
            facingRot += turnRate * timeElapsed;
            wheelRot++;
        }
        centerX += sin(dtor(facingRot)) * speed * timeElapsed;
        centerY += cos(dtor(facingRot)) * speed * timeElapsed;
    }
}
void car::draw() {
    //prepare the matrix
    glMatrixMode(GL_MODELVIEW);

    //translate entire car
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(centerX, suspensionHeight, centerY);
    glRotatef(facingRot, 0, 1, 0);

    //car body
    carmodel.Draw();

    //steering wheel
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0, 1, -1.4);
    glRotatef(turnRate, 0, 0, 1);
    steering.Draw();
    glPopMatrix();

    //chair
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(0, -.2, .5);
    glRotatef(180, 0, 1, 0);
    glScalef(0.4, 1, 1);
    chair.Draw();
    glPopMatrix();
    
    //rear tires
    glPushMatrix();
    glTranslatef(1.3, -.4 - suspensionHeight, 2.3);
    glRotatef(wheelRot, 1, 0, 0);
    glColor3f(0,0,0);
    wheel.Draw();
    glColor3f(.7,.7,.7);
    glPushMatrix();
    glRotatef(-180 * asin(suspensionHeight) / 3.14159, 0, 0, 1);
    suspTop.Draw();
    glPopMatrix();
    hubcap.Draw();
    glRotatef(180, 0, 1, 0);
    glRotatef(wheelRot, 1, 0, 0);
    glTranslatef(2.6, 0, 0);
    glColor3f(0,0,0);
    wheel.Draw();
    glColor3f(.7,.7,.7);
    glPushMatrix();
    glRotatef(-180 * asin(suspensionHeight) / 3.14159, 0, 0, 1);
    suspTop.Draw();
    glPopMatrix();
    hubcap.Draw();
    glPopMatrix();

    //front tires
    glPushMatrix();
    glTranslatef(1.2, -.4 - suspensionHeight, -2.3);
    glRotatef(turnRate, 0, 1, 0);
    glRotatef(wheelRot, 1, 0, 0);
    glColor3f(0,0,0);
    wheel.Draw();
    glColor3f(.7,.7,.7);
    glPushMatrix();
    glRotatef(-180 * asin(suspensionHeight) / 3.14159, 0, 0, 1);
    suspTop.Draw();
    glPopMatrix();
    hubcap.Draw();
    glPopMatrix();    
    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    glTranslatef(1.2, -.4 - suspensionHeight, 2.3);
    glRotatef(turnRate, 0, 1, 0);
    glRotatef(wheelRot, 1, 0, 0);
    glColor3f(0,0,0);
    wheel.Draw();
    glColor3f(.7,.7,.7); 
    glPushMatrix();
    glRotatef(-180 * asin(suspensionHeight) / 3.14159, 0, 0, 1);
    suspTop.Draw();
    glPopMatrix(); 
    hubcap.Draw();
    glPopMatrix();

    glPopMatrix();
}
//car controlls------------------------
void car::addAcceleration(float addAccel) {
    if (speed <= 2 && addAccel > 0 || speed >= -2 && addAccel < 0)
        speed += addAccel;
}
void car::setAcceleration(float newAccel) {
    if (newAccel <= 1) acceleration = newAccel;
}
void car::addTurnRate(float turnChange) {
    if (turnRate < 45 && turnChange > 0 || turnRate > -45 && turnChange < 0) {
        turnRate += turnChange;
    }
}
void car::setTurnRate(float turnDegree) {
    if (turnDegree <= 45 && turnDegree >= -45) {
        turnRate = turnDegree;
    }
}
void car::setSuspension(float height) {
    suspensionHeight = height;
}
void car::increaseSuspension(float height) {
    if(suspensionHeight > 0 && height < 0 || suspensionHeight < .6 && height > 0)
    suspensionHeight += height;
}
//access-------------------------------
void car::setFollowCam() {
    //set up viewing frustum
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    double aspect = double(w) / double(h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, aspect, 1/*znear*/, 50/*zfar*/);

    gluLookAt(0, 10, 10, // eye
            centerX, 0, centerY, // center
            0.0, 1.0, 0.0); // up vector
}
void car::setDriveingCam() {
    //set up viewing frustum
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    double aspect = double(w) / double(h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, aspect, 1/*znear*/, 50/*zfar*/);

    gluLookAt(0, 2.5 + suspensionHeight, 0, // eye
            0, 2 + suspensionHeight, -1, // center
            0.0, 1.0, 0.0); // up vector

    //rotate for proper facing
    glRotatef(-facingRot, 0, 1, 0);
    glTranslatef(-centerX, 0, -centerY);
}
//wheelie------------------------------
void car::wheelie(){
    wheelieup = !wheelieup;
}
//car============================================
