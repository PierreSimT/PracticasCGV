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
		glVertex3f(100,0,0);
		glVertex3f(-100,0,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,green);
		glVertex3f(0,100,0);
		glVertex3f(0,-100,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,blue);
		glVertex3f(0,0,100);
		glVertex3f(0,0,-100);
	glEnd();
}

void cgvScene3D::render(int scene) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the z-buffer

	// lights
  GLfloat light0[]={10,8,9,1}; // point light source
  glLightfv(GL_LIGHT0,GL_POSITION,light0);
  glEnable(GL_LIGHT0);

	glPushMatrix(); // store the model matrices

	  // draw the axes
	  if (axes) draw_axes();

	  // Scene selection based on menu option (int scene)
	  if (scene == SceneA) renderSceneA();
	  else if (scene == SceneB) renderSceneB();

	glPopMatrix (); // restore the modelview matrix
  glutSwapBuffers(); // it is used, instead of glFlush(), to avoid flickering
}


void tube() {
    static GLUquadric* quad = gluNewQuadric();

    GLfloat color_tube[] = { 0,0,0.5 };
    glMaterialfv(GL_FRONT, GL_EMISSION, color_tube);
    gluCylinder(quad, 0.25, 0.25, 1, 15, 15);


}


void cgvScene3D::renderSceneA() {
	GLfloat color_piece[] = { 0,0.25,0 };
	GLfloat color_black[] = { 0,0,0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);
	// TODO: Practice 2a. Part A
	for (float x = 0; x <= 3.0; x+=1.5 )
	{
		for (float y = 0; y <= 3.0; y+=1.5)
		{
			for (float z = 0; z <= 3.0; z+=1.5)
			{
				glPushMatrix();
				glTranslatef(x, y, z);
				glutSolidCube(1);
				glPopMatrix();
			}
		}
	}

	glMaterialfv(GL_FRONT, GL_EMISSION, color_black);
}



void cgvScene3D::renderSceneB() {
	GLfloat color_black[] = { 0,0,0 };
	GLfloat color_piece[] = { 0,0.25,0 };

	// TODO: Practice 2a. Part B.

glTranslatef(-3.0,0,0);
	glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);

	for (float x = 0; x <= 3.0; x += 1.5)
	{
		for (float y = 0; y <= 3.0; y += 1.5)
		{
			for (float z = 0; z <= 3.0; z += 1.5)
			{
				glPushMatrix();
				glTranslatef(x, y, z);
				glutSolidCube(1);
				glPopMatrix();
			}
		}
	}

	// Mostly tubes behind or forward the most outsider cubes
	glPushMatrix();
	glTranslatef(-1, 0, 3.0);
	glRotatef(90, 0, 1, 0);
	tube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4.0, 3.0);
	glRotatef(90, 1, 0, 0);
	tube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 3.0, 3.0);
	glRotatef(90, 0, 1, 0);
	tube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 4.0, 3.0);
	glRotatef(90, 1, 0, 0);
	tube();
	glPopMatrix();

	for (float x = 0; x <= 3.0; x += 1.5)
	{
		glPushMatrix();
		glTranslatef(x, 0, 3.0);
		glRotatef(90, 0, 1, 0);
		tube();
		glPopMatrix();
	}

	for (float y = 0; y <= 3.0; y += 1.5)
	{
		glPushMatrix();
		glTranslatef(0, y, 3.0);
		glRotatef(90, 1, 0, 0);
		tube();
		glPopMatrix();
	}

	for (float x = 0; x <= 3.0; x += 1.5)
	{
		glPushMatrix();
		glTranslatef(x, 3.0, 3.0);
		glRotatef(90, 0, 1, 0);
		tube();
		glPopMatrix();
	}

	for (float y = 0; y <= 3.0; y += 1.5)
	{
		glPushMatrix();
		glTranslatef(3.0, y, 3.0);
		glRotatef(90, 1, 0, 0);
		tube();
		glPopMatrix();
	}

	glMaterialfv(GL_FRONT, GL_EMISSION, color_black);
}
