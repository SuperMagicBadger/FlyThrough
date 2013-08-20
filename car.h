/* 
 * File:   car.h
 * Author: cow
 *
 * Created on October 24, 2011, 11:41 AM
 * 
 * adapted from an example that demonstrates
 * how to open a *.obj file
 * 
 * http://openglsamples.sourceforge.net/files/glut_obj.cpp
 * 
 */

/*
 *
 * Demonstrates how to load and display an Wavefront OBJ file. 
 * Using triangles and normals as static object. No texture mapping.
 *
 * OBJ files must be triangulated!!!
 * Non triangulated objects wont work!
 * You can use Blender to triangulate
 *
 */

#ifndef CAR_H
#define	CAR_H

//includes---------------------------------------
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "entities.h"
#include "model.h"
using namespace std;
//includes=======================================

//defines----------------------------------------
#define dtor(x) x * 3.14159 / 180
enum tires{
	frontRight = 0,
	frontLeft,
	rearRight,
	rearLeft,
	tiresMAX
};
//defines========================================

//prototypes-------------------------------------
class car;
//prototypes=====================================

//definitions------------------------------------
class car : public entity{
public:
	//constructors---------------------
	car();
	~car();
	//updates--------------------------
	virtual void onUpdate(float timeElapsed);
	virtual void draw();
	//controls-------------------------
	void setAcceleration(float newAccel);
	void addAcceleration(float addAccel);
	void setTurnRate(float turnDegree);
	void addTurnRate(float turnChange);
	//suspension controls--------------
	void setSuspension(float height);
	void increaseSuspension(float height);
	//wheelie--------------------------
	void wheelie();
	//access---------------------------
	void setFollowCam();
	void setDriveingCam();
private:
	//drawing variables----------------
	float axelWidthFront;
	float axelWidthBack;
	float carHeight;
	float carLength;
	Model_OBJ carmodel;
	Model_OBJ wheel;
	Model_OBJ steering;
	Model_OBJ chair;
	Model_OBJ hubcap;
	Model_OBJ suspTop;
	//suspension variables-------------
	float suspensionHeight;
	//position data--------------------
	float centerX, centerY;
	float facingRot;
	//movement data--------------------
	float speed;
	float acceleration;
	float turnRate;
	float wheelRot;
	//wheelie--------------------------
	bool wheelieup;
	float wheelieDeg;
	float wheelieMax;
	float wheelieMin;
	float wheelieRate;
};
//definitions====================================

#endif	/* CAR_H */

