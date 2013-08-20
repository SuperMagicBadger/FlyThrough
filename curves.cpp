#include <GL/gl.h>

#include "curves.h"

//curve----------------------------------------------------
//access----------------
int curve::resolution(){
    return numPoints;
}
//manips----------------
void curve::resolution(int res){
    if(numPoints == res) return;
    numPoints = res;
    interpolate();
}
void curve::pushPointBack(Vec point) {
    controlPoints.push_back(point);
    interpolate();
}
void curve::pushPointBack(float x, float y, float z){
    pushPointBack(Vec(x, y, z));
}
void curve::popPointBack() {
    controlPoints.pop_back();
    interpolate();
}
//iterators-------------
vector<Vec>::iterator curve::CRbegin(){
    return curvePoints.begin();
}
vector<Vec>::iterator curve::CRend(){
    return curvePoints.end();
}
vector<Vec>::iterator curve::CPbegin(){
    return controlPoints.begin();
}
vector<Vec>::iterator curve::CPend(){
    return controlPoints.end();
}
//curve====================================================

//curve visualizer-----------------------------------------
//constructors----------
curveVisualizer::curveVisualizer(curve* drawme){
    c = drawme;
}
curveVisualizer::~curveVisualizer(){
    
}
//access----------------
void curveVisualizer::getPosition(float& x, float& y, float& z){
    x = y = z = 0;
}
//update functions------
void curveVisualizer::onUpdate(float timeElapsed){}
void curveVisualizer::draw(){
    vector<Vec>::iterator itr;
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    for(itr = c->CPbegin(); itr != c->CPend(); itr++){
        glVertex3f(itr->x, itr->y, itr->z);
    }
    glColor3f(0, 0, 1);
    for(itr = c->CRbegin(); itr != c->CRend(); itr++){
        glVertex3f(itr->x, itr->y, itr->z);
    }
    glEnd();
}
//curve visualizer=========================================

//lagrange curve-------------------------------------------
float lagrangeCurve::b(float t, int j){
    float ret = 1;    
    for (int i = 0; i < controlPoints.size(); i++) {
        if (i != j) ret *= (t - i) / (j - i);
    }
    return ret;
}
void lagrangeCurve::interpolate(){
    //early exit conitions
    if(controlPoints.size() < 2) return;
    if(numPoints <= 0 ) return;
    
    //inir--------------
    curvePoints.clear();
    curvePoints.resize(numPoints);
    //init==============
    
    //var blok----------
    float h = controlPoints.size() / (float) numPoints;
    float coeff = 0;
    float ytemp = 0;
    float xtemp = 0;
    float ztemp = 0;
    Vec vectemp;
    //var blok==========
    
    //calculate curve---
    for(float t = 0; t < controlPoints.size() - 1; t += h){
        for(int j = 0; j < controlPoints.size(); j++){
            coeff = b(t, j);
            vectemp = vectemp + controlPoints[j] * coeff;
        }
        curvePoints.push_back(vectemp);
    }
    //calculate curve===
}
//lagrange curve===========================================

//bezier curve---------------------------------------------
float bezierCurve::binomialcoeff(int n, int k){
    int b[n + 1];
    b[0] = 1;
    for (int i = 1; i <= n; ++i) {
        b[i] = 1;
        for (int j = i - 1; j > 0; --j) {
            b[j] += b[j - 1];
        }
    }
    return b[k];    
}
float bezierCurve::Bcoeff(float t, int n, int i){
    return binomialcoeff(n, i) * pow(t, i) * pow(1 - t, n - i);    
}
void bezierCurve::interpolate(){
    

    if (numPoints <= 0 || controlPoints.size() < 2) return;
    curvePoints.clear();
  //  curvePoints.resize(numPoints);

    float h = 1.0 / numPoints;
    float bc;
    float xtemp = 0;
    float ytemp = 0;
    float ztemp = 0;
    Vec vectemp;

    for (float i = 0; i <= 1; i += h) {
        for (int j = 0; j < controlPoints.size(); j++) {
            bc = Bcoeff(i, controlPoints.size() - 1, j);
            xtemp += bc * controlPoints[j].x;
            ytemp += bc * controlPoints[j].y;
            ztemp += bc * controlPoints[j].z;
        }
        vectemp.x = xtemp;
        vectemp.y = ytemp;
        vectemp.z = ztemp;
        curvePoints.push_back(vectemp);
        xtemp = 0;
        ytemp = 0;
        ztemp = 0;
    }
}
//bezier curve=============================================

//cr splines-----------------------------------------------
Vec crsplineCurve::eval(int interval, float t){    
    //var blok----------
    Vec ret;
    ret.x = 0;
    ret.y = 0;
    //var blok==========
    
    //early exit conditions--
    if(interval < 2) return ret;
    if(interval > controlPoints.size() - 1) return ret;
    //early exit conditions==
    
    //temps-------------
    const float tsq = t * t;
    const float tcu = tsq * t;
    //temps=============
    
    //coeffs------------
    float b[4];
    
    b[0] = .5 * (-tcu + 2 * tsq - t);
    b[1] = .5 * (3 * tcu - 5 * tsq + 2);
    b[2] = .5 * (-3 * tcu + 4 * tsq + t);
    b[3] = .5 * (tcu - tsq);    
    //coeffs------------
    
    //calculate points--
    for (int i = 0; i < 4; i++) {
        ret = ret + controlPoints[i + interval - 2] * b[i];
    }
    //calculate points==
    return ret;
}
void crsplineCurve::interpolate(){
    //early exit conditions--
    if(numPoints <= 0) return;
    if(controlPoints.size() < 3) return;
    //early exit conditions==
     
    //init--------------
    curvePoints.clear();
    curvePoints.resize(numPoints);
    //init==============
    
    //var blok----------
    const int intervalSteps = numPoints / (curvePoints.size() - 3);
    const float h = 1.0 / intervalSteps;
    //var blok==========
    
    //calculate points--
    for(int interval = 2; interval < controlPoints.size() - 1; interval++){
        for(float t = 0; t <= 1; t += h){
            curvePoints.push_back(eval(interval, t));
        }
    }
    //calculate points==
}
//cr splines===============================================

//bo spline------------------------------------------------
Vec bosplineCurve::eval(int interval, float t){
    //varblok-----------
    Vec ret;
    ret.x = 0;
    ret.y = 0;
    ret.z = 0;
    //varblok===========
    
    //check conditions--
    if (interval < 1) {
        return ret;
    }
    if (interval > controlPoints.size() - 2) {
        return ret;
    }
    //check conditions==
    
    //calculate points--    
    //v_i + and -
    Vec v_not_p = controlPoints[interval + 1] - controlPoints[interval];
    Vec v_not_m = controlPoints[interval] - controlPoints[interval - 1];
    
    Vec v_three_p = controlPoints[interval + 2] - controlPoints[interval + 1];
    Vec v_three_m = controlPoints[interval + 1] - controlPoints[interval];

    //d_i + and -
    const float d_not_p = v_not_p.len();
    const float d_not_m = v_not_m.len();
    
    const float d_three_p = v_three_p.len();
    const float d_three_m = v_three_m.len();
    
    //scale v_i +/-
    v_not_p = v_not_p / d_not_p;
    v_not_m = v_not_m / d_not_m;
    
    v_three_p = v_three_p / d_three_p;
    v_three_m = v_three_m / d_three_m;   

    //find v_i
    Vec vi_not = ((v_not_m * d_not_p) + (v_not_p * d_not_m)) / (d_not_p + d_not_m);
    Vec vi_three = ((v_three_m * d_three_p) + (v_three_p * d_three_m)) / (d_three_p + d_three_m);

    //find p +/-
    Vec ponep = controlPoints[interval] + (vi_not * ((1.0 / 3.0) * d_not_p));    
    Vec pthreem = controlPoints[interval + 1] - (vi_three * ((1.0 / 3.0) * d_three_m));
    
    //find point at t using cubiv bezier curve -- p[i] -> p[i]+  -> p[i+1]- -> p{i+1]
    //(v1 * ((1-t)*(1-t)*(1-t))) + 3 * vc1 * t*(1-t)*(1-t) + 3 * vc2 * t * t * (1-t) + v2*t*t*t
    ret = (controlPoints[interval] * (1-t) * (1-t) * (1-t)) +
          (ponep * 3 * (t) * (1-t) * (1-t)) +
          (pthreem * 3 * (t) * (t) * (1-t)) +
          (controlPoints[interval+1] * (t) * (t) * (t));
    //calculate points==   
    
    return ret;
    
}
void bosplineCurve::interpolate(){
    //conditions---
    if(numPoints <= 0) return;
    if(controlPoints.size() < 3) return;
    //-------------
    
    //const vars---
    //spaced over points - 1 segments
    //using poly.len - 2 points
    const int intervalSteps = numPoints / (controlPoints.size() - 2);
    const float h = 1.0 / intervalSteps;
    curvePoints.clear();
    //const vars===
    
    //iterate over poly------
    //use four points at
    //a time to calculate
    //cr spline
    for (int interval = 1; interval < controlPoints.size() - 2; interval++) {
        for (float t = 0; t <= 1; t += h) {
            curvePoints.push_back(eval(interval, t));
        }
    }
    //iterate over poly======
    
}
//bo spline================================================