#include <cstdlib>
#include <stdio.h>

#include "cgvScene3D.h"

// Constructor methods -----------------------------------

cgvScene3D::cgvScene3D () {
	axes = true;
// Section B: initialize the attributes to control the degrees of freedom of the model
	armRightAngle = 0;
	armLeftAngle = 0;
	goDown = false;

// Section D: initialize the attribute/s that identifies the select object and to colour it yellow

}

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

void cgvScene3D::head() {
	GLfloat color_piece[] = { 0,0.25,0 };
	GLfloat color_black[] = { 0,0,0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);

	glPushMatrix();
	glTranslatef(0, 4, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3.5, 0);
	glScalef(1, 1.3, 1);
	glutSolidCube(0.5);
	glPopMatrix();
}

void cgvScene3D::body() {
	GLfloat color_piece[] = { 0,0.25,0 };
	GLfloat color_black[] = { 0,0,0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);

	glScalef(1, 1, 0.5);
	glutSolidCube(2);
}

void cgvScene3D::rightArm() {
	GLfloat color_piece[] = { 0,0.25,0 };
	GLfloat color_black[] = { 0,0,0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);
	
	glutSolidCube(0.7); // SHOULDER

	glTranslatef(0, -0.35, 0);
	glutSolidCube(0.45); // CODO

	glTranslatef(0, -0.65, 0);
	glScalef(0.35, 0.6, 0.32);
	glutSolidCube(1.5); // FOREARM
}

void cgvScene3D::leftArm() {
	GLfloat color_piece[] = { 0,0.25,0 };
	GLfloat color_black[] = { 0,0,0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);

	glutSolidCube(0.7); // SHOULDER

	glTranslatef(0, -0.35, 0);
	glutSolidCube(0.45); // CODO

	glTranslatef(0, -0.65, 0);
	glScalef(0.35, 0.6, 0.32);
	glutSolidCube(1.5); // FOREARM
}

void cgvScene3D::rightLeg() {
	GLfloat color_piece[] = { 0,0.25,0 };
	GLfloat color_black[] = { 0,0,0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);

	glutSolidCube(0.8);

	glTranslatef(0, -0.68, 0);
	glScalef(0.28, 0.5, 0.28);
	glutSolidCube(2);
}

void cgvScene3D::leftLeg() {
	GLfloat color_piece[] = { 0,0.25,0 };
	GLfloat color_black[] = { 0,0,0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);

	
	glutSolidCube(0.8);

	glTranslatef(0, -0.68, 0);
	glScalef(0.28, 0.5, 0.28);
	glutSolidCube(2);
}

void cgvScene3D::leftFoot() {
	GLfloat color_piece[] = { 0,0.25,0 };
	GLfloat color_black[] = { 0,0,0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);

	glScalef(0.5, 0.25, 0.9);
	glutSolidCube(1);
}

void cgvScene3D::rightFoot() {
	GLfloat color_piece[] = { 0,0.25,0 };
	GLfloat color_black[] = { 0,0,0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, color_piece);

	glScalef(0.5, 0.25, 0.9);
	glutSolidCube(1);
}

void cgvScene3D::render(void) {

	// lights
	GLfloat light0[4]={8.0,8.0,8.0,1}; // point light source  
	glLightfv(GL_LIGHT0,GL_POSITION,light0); // this light is placed here and it remains still 
	glEnable(GL_LIGHT0);
  
  
	// create the model
	glPushMatrix(); // store the model matrices

	  // draw the axes
	  if (axes) draw_axes();

 		//glLightfv(GL_LIGHT0,GL_POSITION,light0); // the light is placed here and it moves with the scene
	  float mesh_color[4] = {1.0, 0.0, 0.0, 1.0}; 
	  glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);

///// Section B: include here the visualization of the tree of the model by using the OpenGL stack of matrices 
/////             it is advisable to create an auxiliary method to encapsulate the code to visualize the model
/////             leaving here only the call to this method. In Section D add the names to the mobile parts of the object by 
/////		          the stack of names and control the selected object to colour it yellow

	glPushMatrix();

	// RIGHT FOOT
	glPushMatrix();
	
	glTranslatef(-0.425, -0.5, 0.16);
	rightFoot();
	
	glPopMatrix();

	//LEFT FOOT
	glPushMatrix();

	glTranslatef(0.425, -0.5, 0.16);
	leftFoot();

	glPopMatrix();

	//LEFT LEG
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0.42, 0.8, 0);
			leftLeg();
		glPopMatrix();
	glPopMatrix();

	//RIGHT LEG
	glPushMatrix();

	glPushMatrix();
		glTranslatef(-0.42, 0.8, 0);
		rightLeg();
	glPopMatrix();

	glPopMatrix();

	//glPopMatrix();

	//BODY
	glPushMatrix();
	glTranslatef(0, 2.22, 0);
	body();
	glPopMatrix();

	// RIGHT ARM
	glPushMatrix();

	glTranslatef(-1.24, 2.7, 0);
	glRotatef(armRightAngle, 1, 0, 0);
	rightArm();

	glPopMatrix();

	// LEFT ARM
	glPushMatrix();

	glTranslatef(1.24, 2.7, 0);
	glRotatef(armLeftAngle, 1, 0, 0);
	leftArm();

	glPopMatrix();

	glPushMatrix();
	head();
	glPopMatrix();

	glPopMatrix (); // restore the modelview matrix 
  
}

void cgvScene3D::rotateOneArm(int arm, float angle) {

	if (arm == 0)
		armRightAngle += angle;
	else
		armLeftAngle += angle;

}
