/* 
 * File:   model.h
 * Author: cow
 *
 * Created on October 31, 2011, 8:57 PM
 */

#ifndef MODEL_H
#define	MODEL_H

//includes---------------------------------------
#include "vec.h"
#include "gs_image.h"
#include "entities.h"
#include <map>
#include <iostream>
#include <fstream>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include<limits.h>
#include <math.h>
using namespace std;
//includes=======================================

//defines----------------------------------------
#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
#define KEY_ESCAPE 27
//defines========================================

//prototypes-------------------------------------
struct face;
class model;
class modelLoader;
class modelVisualizer;
//prototypes=====================================

//definitions------------------------------------
//---------------------------
// FACE
// keeps three indicies for
// use with triangular face
//---------------------------
struct face {
	int ind[3];
};
//---------------------------
// Model
// holds the vertex points,
// normals, etc
//---------------------------
class model {
	friend class modelLoader;

public:
	//constructors------
	model();
	~model();
	//commands----------
	void draw();
	//access------------
	void center(float& x, float& y, float& z);
	void max(float& x, float& y, float& z);
	void min(float& x, float& y, float& z);
	float height();
	float width();
	float depth();	
private:
	void initList();

public:
	//model info--------
	GLint listNumber;
	GLint texNumber;
	GsImage texture;
	vector<Vec> verticies;
	vector<Vec> normals;
	vector<Vec> uvs;
	vector<face> faces;
	//------------------
	
	//sizedata----------
	float hgt, wid, dep;
	float centerx, centery, centerz;
	float highx, highy, highz;
	float lowx, lowy, lowz;
	//------------------
};
//---------------------------
// LOADER
// loads up verticies 'n shit
// from the model file.
// currently works with
//    - PLY
// keeps a back buffer to save
// space/time
//---------------------------
class modelLoader {
public:
	//load/kill functs--
	static model* loadModel(string mFile, string texFile);
	static model* loadModel(string filename);
	static void delModel(model* m);
	
	static int instanceCount(string modelFile);
	static int instanceCount(model* m);
	
private:
	static GsImage loadTex(string tex);
	static model* loadPly(string mod);

	static map<string, model*> modelList;
	static map<model*, int> instances;
};
//---------------------------
// MODEL VIZUALIZER
// allows for the model to be
// displayed in the world.
// keeps track of rot/scale/trans
//---------------------------
class modelVisualizer : public entity {
public:
	//constructors------
	modelVisualizer(model* m);
	modelVisualizer(string model);
	modelVisualizer(string model, string texName);
	~modelVisualizer();
	//access------------
	model* getModel();
	//manips------------
	void translate(float x, float y, float z);
	void rotate(float deg, float x, float y, float z);
	void scale(float x, float y, float z);
	//updates-----------
	void draw();
	void onUpdate(float timeE);
	void getPosition(float& x, float& y, float& z);
private:
	//model info
	model* mod;
	//transformation info
	float tx, ty, tz,
		rd, rx, ry, rz,
		sx, sy, sz;
};
//definitions====================================

#endif	/* MODEL_H */