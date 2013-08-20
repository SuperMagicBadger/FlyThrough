#include "world.h"

//globals----------------------------------------
camera* gcam;
curve* c1;
curve* c2;
curve* c3;
curve* c4;
curveVisualizer* cv1;
curveVisualizer* cv2;
curveVisualizer* cv3;
curveVisualizer* cv4;
//-----------------------------------------------

//main-------------------------------------------
int main(int argc, char** argv) {
    if (!init(argc, argv)) {
        cout << "could not initialize" << endl;
        exit(1);
    }
    world* w = world::getWorld();   
    
   
    //models-----------------    
    modelVisualizer* sky = new modelVisualizer("mmodels/sky.ply", "mmodels/sky.bmp");
    sky->scale(5, 5, 5);
    modelVisualizer* land = new modelVisualizer("mmodels/land.ply", "mmodels/land.bmp");
    modelVisualizer* trees = new modelVisualizer("mmodels/trees.ply", "mmodels/trees.bmp");
    trees->rotate(90, 1, 0, 0);
    trees->translate(-2, .1, .1);
    modelVisualizer* husk = new modelVisualizer("mmodels/husk.ply", "mmodels/husk.bmp");
    husk->scale(.1, .1, .1);
    husk->translate(-1, -.4, -.6);
    modelVisualizer* redstor = new modelVisualizer("mmodels/redstore.ply", "mmodels/redstore.bmp");
    redstor->scale(.1, .15, .1);
    redstor->translate(-.9, -.5, 0.5);
    redstor->rotate(90, 0, 1, 0);
    modelVisualizer* redstor2 = new modelVisualizer("mmodels/redstore.ply", "mmodels/redstore.bmp");
    redstor2->scale(.1, .15, .1);
    redstor2->translate(-.9, -.5, 1);
    redstor2->rotate(90, 0, 1, 0);
    modelVisualizer* resy1 = new modelVisualizer("mmodels/resy.ply", "mmodels/resy.bmp");
    modelVisualizer* resy2 = new modelVisualizer("mmodels/resy.ply", "mmodels/resy.bmp");
    modelVisualizer* resy3 = new modelVisualizer("mmodels/resy.ply", "mmodels/resy.bmp");
    modelVisualizer* resy4 = new modelVisualizer("mmodels/resy.ply", "mmodels/resy.bmp");
    
    resy1->scale(.1,.1,.1);
    resy2->scale(.1,.1,.1);
    resy3->scale(.1,.1,.1);
    resy4->scale(.1,.1,.1);
    
    resy1->translate(-.2, -.38, -.2);
    resy2->translate(.4, -.38, -.2);
    resy3->translate(-.1, -.38, .3);
    resy4->translate(.5, -.38, .3);    
    
    resy3->rotate(180, 0, 1, 0);
    resy4->rotate(180, 0, 1, 0);
    
    modelVisualizer* resy5 = new modelVisualizer("mmodels/resy.ply", "mmodels/resy.bmp");
    modelVisualizer* resy6 = new modelVisualizer("mmodels/resy.ply", "mmodels/resy.bmp");
    modelVisualizer* resy7 = new modelVisualizer("mmodels/resy.ply", "mmodels/resy.bmp");
    modelVisualizer* resy8 = new modelVisualizer("mmodels/resy.ply", "mmodels/resy.bmp");
    
    resy5->scale(.1,.1,.1);
    resy6->scale(.1,.1,.1);
    resy7->scale(.1,.1,.1);
    resy8->scale(.1,.1,.1);
    
    resy5->translate(-.2, -.38, 1.7);
    resy6->translate(.4, -.38, 1.7);
    resy7->translate(-.1, -.38, 2.2);
    resy8->translate(.5, -.38, 2.2);    
    
    resy7->rotate(180, 0, 1, 0);
    resy8->rotate(180, 0, 1, 0);
    //-----------------------
    
    //curve rocket-----------
    c1 = new bezierCurve();
    c1->pushPointBack(-.55, .5, -2.5);
    c1->pushPointBack(-.55, 0, -1.8);
    c1->pushPointBack(-.58, -.4, -.8);
    c1->pushPointBack(-.58, -.4, 0);
    c1->pushPointBack(-.55, -.4, 1);
    c1->pushPointBack(-.55, -.4, 2);
    c1->pushPointBack(-.55, 1, 7);
    c1->resolution(100);
    cv1 = new curveVisualizer(c1);
    //-----------------------
    
    //curve halo-------------
    c2 = new bezierCurve();
    c2->pushPointBack(-1, 1, -1);
    c2->pushPointBack(0, 1, -1);
    c2->pushPointBack(1, 1, -1);
    c2->pushPointBack(1, 1, 0);
    c2->pushPointBack(1, 1, 1);
    c2->pushPointBack(0, 1, 1);
    c2->pushPointBack(-1, 1, 1);
    c2->pushPointBack(-1, 1, 0);
    c2->pushPointBack(-1, 1, -1);
    c2->resolution(100);
    cv2 = new curveVisualizer(c2);
    //-----------------------
    
    //resy path--------------
    c3 = new bosplineCurve();
    c3->pushPointBack(-.55, .5, -3);
    c3->pushPointBack(-.55, .5, -2.5);
    c3->pushPointBack(-.55, -.3, -1.5);
    c3->pushPointBack(-.58, -.4, -.8);
    c3->pushPointBack(-.58, -.4, 0);
    c3->pushPointBack(-.58, -.4, 1);
    c3->pushPointBack(-.58, -.4, 1.5);
    c3->pushPointBack(-.58, -.4, 1.8);
    c3->pushPointBack(-.2, -.4, 2);
    c3->pushPointBack(.4, -.4, 2);
    c3->pushPointBack(1, -.4, 2);
    c3->pushPointBack(1.1, -.4, 2);
    c3->resolution(300); 
    cv3 = new curveVisualizer(c3); 
    //-----------------------
    
    //boat path--------------
    c4 = new bezierCurve();
    c4->pushPointBack(0, -.5, -6);
    c4->pushPointBack(-12, -.5, 0);
    c4->pushPointBack(0, -.5, 12);
    c4->pushPointBack(12, -.5, 0);
    c4->pushPointBack(0, -.5, -6);
    c4->resolution(250);
    //-----------------------
    
    //actors-----------------
    actor* boat = new actor("mmodels/boat.ply", "mmodels/boat.bmp");
    boat->scale(.1, .1, .1);
    
    boat->follow(c4);
    //-----------------------
    
    //camera-----------------
    gcam = new camera();
    gcam->move(0,0,4);
    gcam->face(0,0,0);
    //-----------------------
   
    //load entities----------
    w->addEntity(sky);
    w->addEntity(land);
    w->addEntity(trees);
    w->addEntity(husk);
    w->addEntity(redstor);
    w->addEntity(redstor2);
    w->addEntity(resy1);
    w->addEntity(resy2);
    w->addEntity(resy3);
    w->addEntity(resy4);
    w->addEntity(resy5);
    w->addEntity(resy6);
    w->addEntity(resy7);
    w->addEntity(resy8);
    w->addEntity(boat);
    w->addEntity(gcam);
    //-----------------------
    
    glutMainLoop();
}
//main===========================================

//init-------------------------------------------
bool init(int argc, char** argv) {
    //init glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    //create a window
    glutInitWindowPosition(20, 60);
    glutInitWindowSize(500, 500);
    glutCreateWindow("shitfuck");

    //set up enables
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glPointSize(6);
    glLineWidth(1);
    
    //setup lighting
    GLfloat amb_light[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat diffuse[] = {1, 1, .5, 1};
    GLfloat specular[] = {0.7, 0.7, 0.3, 10};
    GLfloat position[] = {-2, 4, -1, 0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position); 
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //shading
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    
    return true;
}
//init===========================================

//world------------------------------------------
world* world::staticWorld = NULL;

//world constructors-------------------
world* world::getWorld() {
    if (staticWorld == NULL) {
        staticWorld = new world();
    }
    return staticWorld;
}
world::world() {
    //init variables
    fovy = 60;
    rotx = 0;
    roty = 0;
    viewaxis = true;

    
    //load textures-----
    //groundTex.load("ground.bmp");
    
    //set up callbacks
    glutKeyboardFunc(world::keyboard);
    glutSpecialFunc(world::keyboard);
    glutReshapeFunc(world::resize);
    glutDisplayFunc(world::draw);
    glutIdleFunc(world::update);
}
world::~world() {
}
//world tools--------------------------
double world::getTime() {
#ifdef WIN32
    // if better precision is needed in Windows, use QueryPerformanceCounter
    _timeb tp;
    _ftime_s(&tp);
    return 0.001 * (double) tp.millitm + (double) tp.time;
#else
    timeval tp;
    if (gettimeofday(&tp, 0) == -1) return 0;
    return 0.000001 * (double) tp.tv_usec + (double) tp.tv_sec;
#endif

}
//world controlls----------------------
void world::update() {
    //time bookkeeping
    double time = getTime();
    double elapsed = time - staticWorld->lastTime;
    if(elapsed < 1.0/30.0) return;
    staticWorld->lastTime = time;

    //update player then others

    list<entity*>::iterator itr;
    for (itr = staticWorld->objects.begin(); itr != staticWorld->objects.end(); itr++) {
        (*itr)->onUpdate(elapsed);
    }
    glutPostRedisplay();
}
void world::draw() { //uses code borrowed from PAs
    // Clear the rendering buffer:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Clear the model transformation stack:
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Rotate the scene for some simple visualization:
    glRotated(staticWorld->rotx, 1, 0, 0);
    glRotated(staticWorld->roty, 0, 1, 0);     
    
    //draw axis
    //staticWorld->drawaxis(40);
    
    //draw world entities
    list<entity*>::iterator itr;
    for(itr = staticWorld->objects.begin(); itr != staticWorld->objects.end(); itr++){
        (*itr)->draw();
    }

    // Show back buffer:
    glFlush(); // flush the pipeline (usually not necessary)
    glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}
void world::keyboard(unsigned char key, int x, int y) {
    switch(key){
        case 'q':
            gcam->follow(c1);
            staticWorld->rotx = 0;
            staticWorld->roty = 0;
            break;
        case 'w':
            gcam->follow(c2);
            staticWorld->rotx = 0;
            staticWorld->roty = 0;
            break;
        case 'e':
            gcam->follow(c3);
            staticWorld->rotx = 0;
            staticWorld->roty = 0;
            break;
        case 'r':
            gcam->move(0, 0, 4);
            staticWorld->rotx = 0;
            staticWorld->roty = 0;
            break;
        case 'a':
            gcam->watch(c1);
            staticWorld->rotx = 0;
            staticWorld->roty = 0;
            break;
        case 's':
            gcam->watch(c2);
            staticWorld->rotx = 0;
            staticWorld->roty = 0;
            break;
        case 'd':
            gcam->watch(c3);
            staticWorld->rotx = 0;
            staticWorld->roty = 0;
            break;
        case 'f':
            gcam->face(0,0,0);
            staticWorld->rotx = 0;
            staticWorld->roty = 0;
            break;
        case 'l':
            
            break;
        default: return;
    }
}
void world::keyboard(int key, int x, int y) {
    const double incr = 5;
    const double incf = 0.5;
    switch (key) {
        case GLUT_KEY_LEFT: staticWorld->roty -= incr;
            break;
        case GLUT_KEY_RIGHT: staticWorld->roty += incr;
            break;
        case GLUT_KEY_UP: staticWorld->rotx += incr;
            break;
        case GLUT_KEY_DOWN: staticWorld->rotx -= incr;
            break;
        case GLUT_KEY_PAGE_UP: staticWorld->fovy -= incf;
            break;
        case GLUT_KEY_PAGE_DOWN: staticWorld->fovy += incf;
            break;
        default: return; // return without rendering
    }

    // at this point the mark position changed and so we render the scene again:
    glutPostRedisplay();

}
void world::resize(int w, int h) {
    glViewport(0, 0, w, h);
}
//world entity controls----------------
void world::addEntity(entity* e) {
    objects.push_back(e);
}
void world::removeEntity(entity* e) {
    objects.remove(e);
}
//privates-----------------------------
void world::drawaxis(double r){
    double d = r / 20.0;
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3d(-r, 0, 0);
    glVertex3d(r, 0, 0);
    glVertex3d(r - d, -d, 0);
    glVertex3d(r, 0, 0);
    glVertex3d(r - d, d, 0);
    glVertex3d(r, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3d(0, -r, 0);
    glVertex3d(0, r, 0);
    glVertex3d(0, r - d, -d);
    glVertex3d(0, r, 0);
    glVertex3d(0, r - d, d);
    glVertex3d(0, r, 0);

    glColor3f(0, 0, 1);
    glVertex3d(0, 0, -r);
    glVertex3d(0, 0, r);
    glVertex3d(0, -d, r - d);
    glVertex3d(0, 0, r);
    glVertex3d(0, d, r - d);
    glVertex3d(0, 0, r);
 
    glEnd();
}
//world==========================================