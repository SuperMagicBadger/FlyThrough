/* 
 * File:   FlyModel.h
 * Author: cow
 *
 * Created on December 5, 2011, 11:08 PM
 */

#ifndef FLYMODEL_H
#define	FLYMODEL_H

//includes-------------------------------------------------
#include "model.h"
#include "entities.h"
#include <GL/glu.h>
#include <GL/glut.h>
//includes=================================================

//defines--------------------------------------------------
//defines==================================================

//prototypes-----------------------------------------------
class Walker;
//prototypes===============================================

//definitions----------------------------------------------
//---------------------------
//WALKER
// an class that holds together
// models that will be used to
// animate a walking biped
//---------------------------
class walker : public entity{
public:
	//constructors-----------
	static void init();
	walker();
	~walker();
	//access-----------------
	bool walking();
	bool idleing();
	void getPosition(float& x, float& y, float &z);
	//manips-----------------
	void walking(bool walk);
	//updates----------------
	void draw();
	void onUpdate(float timeElapsed);
private:
	//animations-------------
	void returnToNeutral(float time);
	void walk(float time);
	void idle(float time);
	
	//models-----------------
	static Model_PLY Head;
	static Model_PLY Torso;
	static Model_PLY RLeg;
	static Model_PLY LLeg;
	static Model_PLY RArm;
	static Model_PLY LArm;
	
	//controls---------------
	bool toNeutral;
	bool isWalking;
	
	//rotations--------------
	float headTurnRot;
	float headUDRot;
	
	float torsoTurnRot;
	float bodyUDRot;
	
	float armRotL;
	float armRotR;
	float legRotL;
	float legRotR;	
};
//definitions==============================================

#endif	/* FLYMODEL_H */

