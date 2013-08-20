#include <ncurses.h>

#include "city.h"

//city-----------------------------------------------------
//constructors--------------------
city::city(string str){
    load(str);
}
city::city(){
}
city::~city(){
    for(int i = 0; i < maxx; i++){
        for(int j  = 0; j <maxy; j++){
            delete cityblocks[i][j];
        }
        delete cityblocks[i];
    }
    delete cityblocks;
}
void city::load(string str){cout << "loading file: " << str << endl;
    
    //varblok-----------
    ifstream cityfile;
    string templine1;
    string templine2;
    int x, y;
    float xf, yf, zf;
    
    //open/check file---
    cityfile.open(str.c_str());    
    if(!cityfile.good()){
        cityfile.close();
        return;
    }
    //------------------
    
    //get map size------
    cityfile >> x >> y >> xf >> yf >> zf;
    maxx = x;
    maxy = y;
    sx = xf;
    sy = yf;
    sz = zf;
    cityblocks = new modelVisualizer**[x];
    for(int i = 0; i < x; i++){
        cityblocks[i] = new modelVisualizer*[y];
        for(int j = 0; j < y; j++){
            cityblocks[i][j] = NULL;
        }
    }
    cout << x << " " << y << " " << xf << " " << yf << " " << zf << endl;
    //------------------
    
    //load terain-------
    cityfile >> templine1;
    cityfile >> templine2;
    cityfile >> xf >> yf >> zf;
    cout << "loading terrain: " << templine1 << " with tex: " << templine2 << endl;
    terrain = new modelVisualizer(templine1, templine2);
    //------------------
    
    //place models------
    while(!cityfile.eof()){
        cityfile >> x;
        cityfile >> y;
        cityfile >> templine1;
        cout << "loading model: " << templine1 << endl;
        place(x, y, templine1);
    }
    //------------------
    
    //close file--------
    cityfile.close();
    //------------------
    cout << "city loaded" << endl;
    
}
//access--------------------------
modelVisualizer* city::getModel(int x, int y){
    if(x < maxx && x >= 0 && y < maxy && y >= 0)
        return cityblocks[x][y];
    return NULL;
}
//manips--------------------------
void city::setTileSize(float x, float y){
    tilex = x;
    tiley = y;
}
void city::place(int x, int y, string modelname){
    if(x < maxx && x >= 0 && y < maxy && y >= 0){
        model* m = modelLoader::loadModel(modelname);
        cityblocks[x][y] = new modelVisualizer(m);
        cityblocks[x][y]->translate(x * tilex, 0, y * tiley);
        //cityblocks[x][y]->translate();
    }
}
void city::place(int x, int y, model* m){
    if(x < maxx && x >= 0 && y < maxy && y >= 0){
        cityblocks[x][y] = new modelVisualizer(m);
    }
}
void city::killModel(int x, int y){
    if(x < maxx && x >= 0 && y < maxy && y >=0){
        delete cityblocks[x][y];
        cityblocks[x][y] = NULL;
    }
}
//updates-------------------------
void city::draw(){
    list<modelVisualizer*>::iterator itr;
    for(itr = objects.begin(); itr != objects.end(); itr++){
        (*itr)->draw();
    }
}
void city::onUpdate(float timeE){
    list<modelVisualizer*>::iterator itr;
    for(itr = objects.begin(); itr != objects.end(); itr++){
        (*itr)->onUpdate(timeE);
    }
}
void city::getPosition(float& x, float& y, float& z){
    x = y = z = 0;
}
//city=====================================================
