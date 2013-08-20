/* 
 * File:   decor.h
 * Author: cow
 *
 * Created on November 1, 2011, 1:43 AM
 */

#ifndef DECOR_H
#define	DECOR_H

//includes---------------------------------------
#include "entities.h"
#include "model.h"
#include <map>
#include <string>
#include <GL/gl.h>
#include <GL/glut.h>
//includes=======================================

//defines----------------------------------------
//defines========================================

//prototypes-------------------------------------
class decoration;
class modelList;
//prototypes=====================================

//definitions------------------------------------
//----------------------
//DECOR
// a class that can display
// a single textured model
//----------------------
class decoration : public entity{
public:
	//construcotrs---------------------
	decoration();
	~decoration();
	//load information-----------------
	void LoadOBJ(char* file);
	void LoadTex(char* file);
	//entity---------------------------
	void draw();
	void onUpdate(float timeElapsed);
	void getPosition(float& x, float& y, float& z);
	//position manipulation------------
	void translate(float x, float y, float z);
	void scale(float x, float y, float z);
	void rotate(float deg, float x, float y, float z);	
	//material manipulation------------
	void setColor(float r, float g, float b);
private:
	//model info
	Model_PLY decor;
	float tX, tY, tZ;
	float sX, sY, sZ;
	float rD, rX, rY, rZ;
	//material info
	GLfloat matColor[4];
	float r, g, b;
};
//----------------------
// Model List
// a list that keeps track
// of previously used textures
// to save on memory space
//----------------------
class modelList{
public:
	Model_OBJ* getModelOBJ(string str);
	Model_PLY* getModelPLY(string str);
private:
	map<string, Model_PLY*> plymodels;
	map<string, Model_OBJ*> objmodels;
};
//definitions====================================

#endif	/* DECOR_H */

