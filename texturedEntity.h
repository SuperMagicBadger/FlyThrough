/* 
 * File:   texturedEntity.h
 * Author: cow
 *
 * Created on November 1, 2011, 5:13 PM
 */

#ifndef TEXTUREDENTITY_H
#define	TEXTUREDENTITY_H

//includes---------------------------------------
#include <GL//gl.h>
#include <GL/glut.h>
#include <cmath>
#include "gs_image.h"
#include "entities.h"
//includes=======================================

//defines----------------------------------------
//defines========================================

//prototypes-------------------------------------
class texturedCube;
//prototypes=====================================

//definitions------------------------------------
class texturedCube : public entity{
public:
	//constructors------
	texturedCube(char* texFile);
	~texturedCube();
	//entity------------
	void draw();
	void onUpdate(float timeElapsed);
	//stuff-------------
	void translate(float x, float y, float z);
	void scale(float s);
	void rotate(float deg, float x, float y, float z);
private:
	float s;
	float tX, tY, tZ;
	float rD, rX, rY, rZ;
	GsImage tex;
};
/*
class TexturedCone : public entity{
public:
	//constructors------
	texturedCone(float height, float base, char* texFile);
	~texturedCone();
	//entity------------
	void draw();
	void onUpdate(float timeElapsed);
private:
	float h, b;
	GsImage tex;
};
*/
//definitions====================================

#endif	/* TEXTUREDENTITY_H */

