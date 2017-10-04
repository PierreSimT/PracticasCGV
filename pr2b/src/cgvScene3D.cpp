#include <cstdlib>
#include <stdio.h>

#include "cgvScene3D.h"

// Constructor methods -----------------------------------

cgvScene3D::cgvScene3D () {axes = true;}

cgvScene3D::~cgvScene3D() {}


// Public methods ----------------------------------------

void draw_axes(void) {
  GLfloat red[]={1,0,0,1.0};
  GLfloat green[]={0,1,0,1.0};
  GLfloat blue[]={0,0,1,1.0};

	glBegin(GL_LINES);
    glMaterialfv(GL_FRONT,GL_EMISSION,red);
		glVertex3f(1000,0,0);
		glVertex3f(-1000,0,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,green);
		glVertex3f(0,1000,0);
		glVertex3f(0,-1000,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,blue);
		glVertex3f(0,0,1000);
		glVertex3f(0,0,-1000);
	glEnd();
}

void draw_tube() {
  GLUquadricObj *tube;
  GLfloat color_tube[]={0,0,0.5};

  glMaterialfv(GL_FRONT,GL_EMISSION,color_tube);
  
  tube=gluNewQuadric();
  gluQuadricDrawStyle(tube,GLU_FILL);

	glPushMatrix();
	glTranslatef(0,0,-0.5);
  gluCylinder(tube,0.25,0.25,1,20,20);
	glPopMatrix();

  gluDeleteQuadric(tube);
}

void cgvScene3D::render(void) {
// TODO: Modify this function in order to define additional clipping planes according to the instructions of the practice. 

	// lights
  GLfloat light0[]={10,8,9,1}; // point light source
  glLightfv(GL_LIGHT0,GL_POSITION,light0);
  glEnable(GL_LIGHT0);

	// create the model
	glPushMatrix(); // store the model matrices

	  // draw the axes
	  if (axes) draw_axes();

		// draw the objects of the scene
    GLfloat color_cube[]={0,0.25,0};
    glMaterialfv(GL_FRONT,GL_EMISSION,color_cube);

		glPushMatrix();
			glScalef(1,2,4);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glRotatef(45,1,0,0);
			glScalef(1,1,4.5);
			draw_tube();
		glPopMatrix();
		glPushMatrix();
			glRotatef(-45,1,0,0);
			glScalef(1,1,4.5);
			draw_tube();
		glPopMatrix();
	
	glPopMatrix (); // restore the modelview matrix 
  
}

