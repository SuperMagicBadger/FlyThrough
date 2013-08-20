/* 
 * File:   camera.h
 * Author: cow
 *
 * Created on December 2, 2011, 12:55 PM
 */

#ifndef CAMERA_H
#define	CAMERA_H

//includes-------------------------------------------------
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "curves.h"
#include "entities.h"
//includes=================================================

//defines--------------------------------------------------
//defines==================================================

//prototypes-----------------------------------------------
class camera;
//prototypes===============================================

//definitions----------------------------------------------
//camera----------------
// sits still or can be
// forced to follow or
// watch an entity/curvce
//----------------------
class camera : public entity{
public:
	//constructors------
	camera();
	~camera();
	//access------------
	void getPosition(float &x, float &y, float &z);
	//manips------------
	void follow(entity* e);
	void follow(curve* c);
	void watch(entity* e);
	void watch(curve* c);
	void move(float x, float y, float z);
	void face(float x, float y, float z);
	//update functions--
	void draw();
	void onUpdate(float timeElapsed);
private:
	//position data
	float posx, posy, posz;
	float facx, facy, facz;
	//follow functions
	entity* followedE;
	entity* watchedE;
	curve* followedC;
	curve* watchedC;
	vector<Vec>::iterator followedItr, watchedItr;	
	//time functions
	float time;
};
//definitions==============================================

#endif	/* CAMERA_H */

