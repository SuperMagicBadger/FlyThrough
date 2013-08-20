/* 
 * File:   world.h
 * Author: cow
 *
 * Created on October 24, 2011, 11:40 AM
 */

#ifndef WORLD_H
#define	WORLD_H

//includes---------------------------------------
#ifdef WIN32
#include <glut/glut.h>
#include <sys/times.h>
#include <sys/timeb.h>
#else
#include <GL/glut.h>
#include <sys/time.h>
#endif
#include "gs_image.h"
#include <iostream>
#include <list>
#include "entities.h"
#include "curves.h"
#include "model.h"
#include "actor.h"
#include "camera.h"
using namespace std;
//includes=======================================

//defines----------------------------------------
#define playerAcceleration 0.1
#define playerTurnRate 0.5
//defines========================================

//prototypes-------------------------------------
int main(int argc, char** argv);
bool init(int argc, char** argv);
class world;
//prototypes=====================================

//definitions------------------------------------
class world {
public:
	//constructors---------------------
	static world* getWorld();
	~world();
	//tools----------------------------
	static double getTime();
	//controls-------------------------
	static void update();
	static void draw();
	static void keyboard(unsigned char key, int x, int y);
	static void keyboard(int key, int x, int y);
	static void resize(int w, int h);
	//entities-------------------------
	void addEntity(entity* e);
	void removeEntity(entity* e);
private:
	void drawaxis(double r);
	//static instance------------------
	world();
	static world* staticWorld;
	//entities-------------------------
	list<entity*> objects;
	//controll information-------------
	double lastTime;
	//view information-----------------
	bool chaseCam;
	double fovy;
	bool viewaxis;
	double rotx, roty;
	double n, r, g, b;
};
//definitions====================================

#endif	/* WORLD_H */

