#include "model.h" 

//Model----------------------------------------------------
//constructors---------------
model::model() {
    listNumber = -1;
    hgt = wid = dep = 0; 
    centerx = centery = centerz = 0;
    lowx = lowy = lowz = 0;
    highx = highy = highz = 0;
}
model::~model() {
    if (listNumber != -1)
        glDeleteLists(listNumber, 1);
}
//commands-------------------
void model::draw() {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texNumber);
        glCallList(listNumber);
        glDisable(GL_TEXTURE_2D);
}
//access---------------------
float model::height() {
    return hgt;
}
float model::width() {
    return wid;
}
float model::depth() {
    return dep;
}
void model::center(float& x, float& y, float& z){
    x = centerx;
    y = centery;
    z = centerz;
}
void model::max(float& x, float& y, float& z){
    x = highx;
    y = highy;
    z = highz;
}
void model::min(float& x, float& y, float& z){
    x = lowx;
    y = lowy;
    z = lowz;
}
void model::initList() {
    //calculate controll pts-
    centerx = (highx + lowx) / 2;
    centery = (highy + lowy) / 2;
    centerz = (highz + lowz) / 2;
    
    wid = sqrt(highx * highx + lowx * lowx);
    hgt = sqrt(highy * highy + lowy * lowy);
    dep = sqrt(highz * highz + lowz * lowz);
    
    cout << centerx << " " <<  centery << " " << centerz << endl;
    cout << highx << " " <<  highy << " " << highz << endl;
    cout << lowx << " " <<  lowy << " " << highz << endl;
    cout << wid << " " <<  hgt << " " << dep << endl;
    //-----------------------
    
    listNumber = glGenLists(1);
    float x, y, z;

    glNewList(listNumber, GL_COMPILE);
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < faces.size(); i++) {
        for (int j = 0; j < 3; j++) {
            //normals
            x = normals[faces[i].ind[j]].x;
            y = normals[faces[i].ind[j]].y;
            z = normals[faces[i].ind[j]].z;
            glNormal3f(x, y, z);
            //uv points
            x = uvs[faces[i].ind[j]].x;
            y = uvs[faces[i].ind[j]].y;
            glTexCoord2f(x, y);
            //vertex
            x = verticies[faces[i].ind[j]].x;
            y = verticies[faces[i].ind[j]].y;
            z = verticies[faces[i].ind[j]].z;
            glVertex3f(x, y, z);
        }
    }

    glEnd();
    glEndList();
}
//Model====================================================

//loader---------------------------------------------------
//statics--------------------
map<string, model*> modelLoader::modelList;
map<model*, int> modelLoader::instances;
//load/kill functs-----------
model* modelLoader::loadModel(string mFile, string texFile) {
    //varblok------
    model* ret = NULL;
    //-------------

    //check if laready loaded
    if (modelList.find(mFile) != modelList.end()
            && instances[modelList[mFile]] > 0) {
        ret = modelList[mFile];
        instances[ret]++;
        return ret;
    }
    //-----------------------

    //load model-------------
    if (mFile.find(".ply") != string::npos) {
        ret = loadPly(mFile);
        ret->texture.load(texFile.c_str());
        ret->texNumber = ret->texture.ogl_bind_texture();
    }
    //-----------------------

    //increment model count--
    if(ret != NULL){
        instances[ret]++;
    }
    //-----------------------
    
    return ret;
}
model* modelLoader::loadModel(string filename) {
    return loadModel(filename, "");
}
model* modelLoader::loadPly(string mod) {
    //varblok-----------
    model* ret = NULL;
    float tx, ty, tz;
    string str;
    int tverts;
    int tfaces;
    //------------------

    //open the file-----
    ifstream modelFile;
    modelFile.open(mod.c_str());
    if (!modelFile.good()) {
        modelFile.close();
        return ret;
    }
    //------------------

    //skip the header---
    do {
        modelFile >> str;
        if (str.compare("vertex") == 0) {
            modelFile >> tverts;
        }
        if (str.compare("face") == 0) {
            modelFile >> tfaces;
        }
    } while (str.compare("end_header") != 0);
    //------------------

    //new model---------
    ret = new model();
    ret->lowx = ret->lowy = ret->lowz = INT_MAX;
    ret->highx = ret->highy = ret->highz = INT_MIN;
    ret->verticies.reserve(tverts);
    ret->normals.reserve(tverts);
    ret->faces.reserve(tfaces);
    //------------------

    //load verticies----    
    for (int i = 0; i < tverts; i++) {
        modelFile >> tx;
        modelFile >> ty;
        modelFile >> tz;
        ret->verticies.push_back(Vec(tx, ty, tz));
        if(ret->highx < tx){
            ret->highx = tx;
        } else if(ret->lowx > tx) {
            ret->lowx = tx;
        }
        if(ret->highy < ty){
            ret->highy = ty;
        } else if (ret->lowy > ty){
            ret->lowy = ty;
        }
        if(ret->highz < tz){
            ret->highz = tz;
        } else if(ret->lowz > tz){
            ret->lowz = tz;
        }
        modelFile >> tx;
        modelFile >> ty;
        modelFile >> tz;
        ret->normals.push_back(Vec(tx, ty, tz));
        modelFile >> tx;
        modelFile >> ty;
        ret->uvs.push_back(Vec(tx, ty, 0));
    }
    //------------------

    //load faces--------
    int junk;
    face tf;
    for (int i = 0; i < tfaces; i++) {
        modelFile >> junk;
        modelFile >> tf.ind[0];
        modelFile >> tf.ind[1];
        modelFile >> tf.ind[2];
        ret->faces.push_back(tf);
    }
    //------------------

    //clean up----------
    ret->initList();
    modelFile.close();
    // ret->initList();
    return ret;
    //------------------
}
void modelLoader::delModel(model* m){
    instances[m]--;
    if(instances[m] <= 0){
        delete m;
    }
}
int modelLoader::instanceCount(model* m){
    if(instances.find(m) == instances.end()){
        return 0;
    }
    return instances[m];
}
int modelLoader::instanceCount(string modelFile){
    if(modelList.find(modelFile) == modelList.end()){
        return 0;
    }
    return instances[modelList[modelFile]];
}
//loader===================================================

//model vizualizer-----------------------------------------
//constructors---------------
modelVisualizer::modelVisualizer(model* m) {
    mod = m;
    tx = ty = tz = rd = rx = ry = rz = 0;
    sx = sy = sz = 1;
}
modelVisualizer::modelVisualizer(string modelname) {
    mod = modelLoader::loadModel(modelname);
    tx = ty = tz = rd = rx = ry = rz = 0;
    sx = sy = sz = 1;
}
modelVisualizer::modelVisualizer(string modelname, string texname) {
    mod = modelLoader::loadModel(modelname, texname);
    tx = ty = tz = rd = rx = ry = rz = 0;
    sx = sy = sz = 1;
}
modelVisualizer::~modelVisualizer() {
    //  modelLoader::delModel(mod);
    mod = NULL;
}
//access---------------------
model* modelVisualizer::getModel(){
    return mod;
}
//manips---------------------
void modelVisualizer::translate(float x, float y, float z) {
    tx = x;
    ty = y;
    tz = z;
}
void modelVisualizer::rotate(float deg, float x, float y, float z) {
    rd = deg;
    rx = x;
    ry = y;
    rz = z;
}
void modelVisualizer::scale(float x, float y, float z) {
    sx = x;
    sy = y;
    sz = z;
}
//updates--------------------
void modelVisualizer::draw() {
    glPushMatrix();
    glTranslatef(tx, ty, tz);
    glScalef(sx, sy, sz);
    glRotatef(rd, rx, ry, rz);
    mod->draw();
    glPopMatrix();
}
void modelVisualizer::onUpdate(float timeE) {

}
void modelVisualizer::getPosition(float& x, float& y, float& z) {
    mod->center(x, y, z);
    x += tx;
    y += ty;
    z += tz;
}
//model vizualizer=========================================
