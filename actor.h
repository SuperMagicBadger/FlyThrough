/* 
 * File:   actor.h
 * Author: cow
 *
 * Created on December 15, 2011, 2:02 PM
 */

#ifndef ACTOR_H
#define	ACTOR_H

//includes-------------------------------------------------
#include "model.h"
#include "curves.h"
#include <vector>
#include <string>
using namespace std;
//includes=================================================

//prototypes-----------------------------------------------
class actor;
//prototypes===============================================

//definitions----------------------------------------------
class actor : public modelVisualizer{
public:
	//constructors----------------
	actor(model* m) : modelVisualizer(m){followed = NULL;}
	actor(string mod) : modelVisualizer(mod){followed = NULL;}
	actor(string mod, string tex) : modelVisualizer(mod, tex){followed = NULL;}
	//manips----------------------
	void follow(curve* c);
	//updates---------------------
	void onUpdate(float timeE);
private:
	vector<Vec>::iterator itr;
	curve* followed;
};
//definitions==============================================

#endif	/* ACTOR_H */

