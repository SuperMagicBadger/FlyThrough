/* 
 * File:   curves.h
 * Author: cow
 *
 * Created on November 28, 2011, 12:01 PM
 */

#ifndef CURVES_H
#define	CURVES_H

//includes---------------------------------------
#include "vec.h"
#include "entities.h"
#include <vector>
#include <cmath>
using namespace std;
//includes=======================================

//defines----------------------------------------
//defines========================================

//prototypes-------------------------------------
class curve;
class curveVisualizer;
class lagrangeCurve;
class bezierCurve;
class bezierSpline;
class crsplineCurve;
//prototypes=====================================

//definitions------------------------------------
//---------------------------
//CURVE
//the base class for an
//interpolating curve
//---------------------------
class curve{
public:
	//access-----------------
	int resolution();
	//manips-----------------
	void resolution(int res);
	void pushPointBack(Vec point);
	void pushPointBack(float x, float y, float z);
	void popPointBack();
	//iterator---------------
	vector<Vec>::iterator CRbegin();
	vector<Vec>::iterator CRend();
	vector<Vec>::iterator CPbegin();
	vector<Vec>::iterator CPend();
protected:
	//internals
	virtual void interpolate() = 0;
	
	vector<Vec> controlPoints;
	vector<Vec> curvePoints;
	int numPoints;
};
//---------------------------
//Curve Visualizer
//draws a curve on screen
//using GL_POINTS
//---------------------------
class curveVisualizer : public entity{
public:
	//constructors-----------
	curveVisualizer(curve* drawme);
	~curveVisualizer();
	//access-----------------
	void getPosition(float &x, float &y, float &z);
	//update functions-------
	void draw();
	void onUpdate(float timeElapsed);
private:
	curve* c;
};
//---------------------------
//LAGRANGE
//uses the lagrange interpolating
//polynomial
//---------------------------
class lagrangeCurve : public curve{
protected:
	float b(float t, int j);
	void interpolate();
};
//---------------------------
//BEZIER CURVE
//---------------------------
class bezierCurve : public curve{
protected:
	float binomialcoeff(int n, int k);
	float Bcoeff(float t, int n, int i);
	void interpolate();
};
//---------------------------
//CATMUL ROM SPLINES
//---------------------------
class crsplineCurve : public curve{
protected:
	Vec eval(int interval, float t);
	void interpolate();
};
//---------------------------
//BO SPLINES-----------------
//---------------------------
class bosplineCurve : public curve{
protected:
	Vec eval(int interval, float t);
	void interpolate();
};
//---------------------------
//definitions====================================

#endif	/* CURVES_H */

