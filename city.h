/* 
 * File:   city.h
 * Author: cow
 *
 * Created on December 13, 2011, 12:20 PM
 */

#ifndef CITY_H
#define	CITY_H

//includes-------------------------------------------------
#include "entities.h"
#include "model.h"
#include <fstream>
#include <iostream>
#include <list>
using namespace std;
//includes=================================================

//defines--------------------------------------------------
//defines==================================================

//prototypes-----------------------------------------------
class city;
//prototypes===============================================

//definitions----------------------------------------------
class city : public entity{
public:
	//constructors-----------
	city(string filename);
	city();
	~city();
	void load(string str);
	//access-----------------
	modelVisualizer* getModel(int x, int y);
	//manips-----------------
	void setTileSize(float x, float y);
	void place(int x, int y, string modelname);
	void place(int x, int y, model* m);	
	void killModel(int x, int y);
	//updaters---------------
	void draw();
	void onUpdate(float timeE);
	void getPosition(float &x, float &y, float& z);
private:
	list<modelVisualizer*> objects;
	
	float tx, ty, tz;
	float sx, sy, sz;
	float rd, rx, ry, rz;
};
//definitions==============================================


#endif	/* CITY_H */

