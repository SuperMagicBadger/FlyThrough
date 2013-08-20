
#include "texturedEntity.h"


# define MINRADIUS 0.00001
# define PI        3.1415926535897932


//support code from crops
void draw_wire_tube ( double len, double rt, double rb, int nfaces )
 {
   if ( rb<=0 ) rb=MINRADIUS;
   if ( rt<=0 ) rt=MINRADIUS;
   if ( nfaces<3 ) nfaces = 3;
   
   // compute vertical axis:
   double dang = (2.0*PI)/double(nfaces);
   double ang = 0;

   // we will use len as half the length:
   len = len/2;

   // initial points:
   double ibx=rb, iby=-len, ibz=0; // bottom
   double itx=rt, ity=+len, itz=0; // top

   // current points start as the initial points:
   double cbx=ibx, cby=iby, cbz=ibz; // bottom
   double ctx=itx, cty=ity, ctz=itz; // top

   // declare the "next points" to form the cylinder lines:
   double nbx, nby, nbz; // bottom
   double ntx, nty, ntz; // top

   // compute the points all around body:
   int i=1;
   glBegin ( GL_POLYGON );
   do { // rotate the current points:
        if ( i<nfaces ) // normal rotation for intermediate points
         { ang += dang;
           double ca = cos(ang);
           double sa = sin(ang);
           nbx=ca*rb; nby=cby; nbz=sa*rb;
           ntx=ca*rt; nty=cty; ntz=sa*rt;
         }
        else // to make a perfect closure, the last points are exactly the first ones
         { nbx=ibx; nby=iby; nbz=ibz;
           ntx=itx; nty=ity; ntz=itz;
         }

        // draw bottom boundary:
        glVertex3d ( cbx, cby, cbz ); glVertex3d ( nbx, nby, nbz );
        // draw top boundary:
        glVertex3d ( ctx, cty, ctz ); glVertex3d ( ntx, nty, ntz );
        // draw vertical line:
        glVertex3d ( cbx, cby, cbz ); glVertex3d ( ctx, cty, ctz );
        // draw top and bottom line to center (optional):
        glVertex3d ( ctx, cty, ctz ); glVertex3d ( 0, +len, 0 );
        glVertex3d ( cbx, cby, cbz ); glVertex3d ( 0, -len, 0 );

        // update current points:
        cbx=nbx; cby=nby; cbz=nbz;
        ctx=ntx; cty=nty; ctz=ntz;
        
        // increment side counter:
        i++;
      } while ( i<=nfaces );

   // draw the last line:
   glEnd();
 }

//textured cube--------------------------------------------
//constructors-------------------------
texturedCube::texturedCube(char* texFile){
    tex.load(texFile);
}
texturedCube::~texturedCube(){
    
}
//entity-------------------------------
void texturedCube::draw(){
    glPushMatrix();
    glScalef(s, s, s);
    glTranslatef(tX, tY, tZ);
    glRotatef(rD, rX, rY, rZ);
    glBegin(GL_POLYGON);
    
    draw_wire_tube(1, 1, 1, 4);
    

    glEnd();
    glPopMatrix();
}
void texturedCube::onUpdate(float timeElapsed){
    
}
//stuff--------------------------------
void texturedCube::translate(float x, float y, float z){
    tX = x;
    tY = y;
    tZ = z;
}
void texturedCube::scale(float sc){
    s = sc;
}
void texturedCube::rotate(float deg, float x, float y, float z){
    rD = deg;
    rX = x;
    rY = y;
    rZ = z;
}
//texturedCube=============================================

//texturedCone---------------------------------------------
//texturedCone=============================================