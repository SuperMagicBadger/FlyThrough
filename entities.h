/* 
 * File:   entities.h
 * Author: cow
 *
 * Created on October 24, 2011, 11:59 AM
 */

#ifndef ENTITIES_H
#define	ENTITIES_H

//includes---------------------------------------
#include <GL/glut.h>
//includes=======================================

//prototypes-------------------------------------
class entity;
//prototypes=====================================

//definitions------------------------------------
class entity{
public:
	//positions functions---------
	virtual void getPosition(float &x, float &y, float &z) = 0;
	//update functions------------
	virtual void onUpdate(float timeElapsed) = 0;
	virtual void draw() = 0;
private:
};
//definitions====================================

#endif	/* ENTITIES_H */

